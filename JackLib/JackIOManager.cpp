#include <iostream>
#include "JackIOManager.h"
#include "AudioSource2I.h"
#include "AudioRendererI.h"
#include "MidiInputHandlerI.h"
#include "MidiSourceI.h"
#include <jack/midiport.h>

namespace
{

int JackProcessFunction(jack_nframes_t NumFrames, void* arg)
{
    return ((CJackIOManager*)arg)->OnProcess(NumFrames);
}

void JackShutdownFunction(void* arg)
{
    ((CJackIOManager*)arg)->OnShutdown();
}

}

CJackIOManager::CJackIOManager()
 : m_Client(0)
 , m_SamplingFrequency(-1)
 , m_AudioOutputPort(0)
 , m_AudioSource()
 , m_AudioInputPort(0)
 , m_AudioRenderer()
 , m_MidiInputPort(0)
 , m_MidiHandler()
 , m_MidiOutputPort(0)
 , m_MidiSource()
{
}

CJackIOManager::~CJackIOManager()
{
    CloseClient();
}

bool CJackIOManager::OpenClient(const std::string &ClientName)
{
    bool Success = false;
    // open client with requested name. No further options are needed
    m_Client = jack_client_open(ClientName.c_str(), JackNullOption, 0);
    if(m_Client)
    {
        // retrieve and display the current sample rate.
        m_SamplingFrequency = jack_get_sample_rate(m_Client);

        // tell the JACK server to call `jack_shutdown()' if it ever shuts down,
        // either entirely, or if it just decides to stop calling us.
        jack_on_shutdown(m_Client,
                         JackShutdownFunction,
                         this);

        // tell the JACK server to call `process()' whenever there is work to be done.
        if(0==jack_set_process_callback(m_Client,
                                        JackProcessFunction,
                                        this))
        {
            Success = true;
        }
        else
        {
            std::cerr << "Failed to set process callback for client " << ClientName << std::endl;
        }
    }

    if(!Success)
    {
        // make sure everything is cleaned ip, even if just one step failed
        CloseClient();
    }

    return Success;
}

bool CJackIOManager::OpenAudioOutput(const std::string &Name, std::shared_ptr<IAudioSource2> AudioSource)
{
    bool Success = false;
    if(m_Client)
    {
        // create one output port. Use default audio type, which is mono float 32 bits.
        // it is adviced to use 'terminal' option for audio synthesizers.
        m_AudioOutputPort = jack_port_register(m_Client, Name.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput|JackPortIsTerminal, 0);
        if(m_AudioOutputPort)
        {
            m_AudioSource = AudioSource;
            Success = true;
        }
    }
    return Success;
}

bool CJackIOManager::OpenAudioInput(const std::string &Name, std::shared_ptr<IAudioRenderer> AudioRenderer)
{
    bool Success = false;
    if(m_Client)
    {
        // create one input port. Use default audio type, which is mono float 32 bits.
        // it is adviced to use 'terminal' option ???.
        m_AudioInputPort = jack_port_register(m_Client, Name.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput|JackPortIsTerminal, 0);
        if(m_AudioInputPort)
        {
            m_AudioRenderer = AudioRenderer;
            Success = true;
        }
    }
    return Success;
}

bool CJackIOManager::OpenMidiInput(const std::string &Name, std::shared_ptr<IMidiInputHandler> MidiHandler)
{
    bool Success = false;
    if(m_Client)
    {
        m_MidiInputPort = jack_port_register(m_Client, Name.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput|JackPortIsTerminal, 0);//use JackPortIsTerminal ?
        if(m_MidiInputPort)
        {
            m_MidiHandler = MidiHandler;
            Success = true;
        }
    }
    return Success;
}

bool CJackIOManager::OpenMidiOutput(const std::string &Name, std::shared_ptr<IMidiSource> MidiSource)
{
    bool Success = false;
    if(m_Client)
    {
        m_MidiOutputPort = jack_port_register(m_Client, Name.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput|JackPortIsTerminal, 0);//use JackPortIsTerminal ?
        if(m_MidiOutputPort)
        {
            m_MidiSource = MidiSource;
            Success = true;
        }
    }
    return Success;
}

void CJackIOManager::CloseClient()
{
    if(m_Client)
    {
        if(m_AudioOutputPort)
        {
            jack_port_unregister(m_Client, m_AudioOutputPort);
            m_AudioOutputPort = 0;
        }
        if(m_AudioInputPort)
        {
            jack_port_unregister(m_Client, m_AudioInputPort);
            m_AudioInputPort = 0;
        }
        if(m_MidiInputPort)
        {
            jack_port_unregister(m_Client, m_MidiInputPort);
            m_MidiInputPort = 0;
        }
        // tell jack we do not want to play along anymore
        jack_deactivate(m_Client);
        // close and remove the client
        jack_client_close(m_Client);
        // make sure we know we are closed
        m_Client = 0;
    }
}

bool CJackIOManager::ClientIsOpen() const
{
    return 0!=m_Client;
}


int CJackIOManager::SamplingFrequency() const
{
    return static_cast<int>(m_SamplingFrequency);
}

int CJackIOManager::OnProcess(jack_nframes_t NumFrames)
{
    // if this function is called, it is fair to assume we are opened (so m_Client exists)
    int ReturnValue = 0;
    jack_nframes_t TimeStamp = jack_last_frame_time(m_Client);
    // handle midi input before generating audio
    if(m_MidiInputPort && m_MidiHandler)
    {
        int NumConnected = jack_port_connected(m_MidiInputPort);
        if(0<NumConnected)
        {
            void* SrcBuffer = jack_port_get_buffer(m_MidiInputPort, NumFrames);
            jack_nframes_t NumEvents = jack_midi_get_event_count(SrcBuffer);
            if(0<NumEvents)
            {
                jack_nframes_t EventIndex = 0;
                while(EventIndex<NumEvents)
                {
                    jack_midi_event_t MidiEvent;
                    if(0==jack_midi_event_get(&MidiEvent, SrcBuffer, EventIndex))
                    {
                        // handle:
                        // Note on  : 3 bytes 0x9x MidiNote [0,127] Velocity [0,127] -> msb always 0
                        // Note off : 3 bytes 0x8x MidiNote [0,127] Velocity [0,127] -> msb always 0
                        // Controll : 3 bytes 0xBx Param    [0,127] Value    [0,127] -> msb always 0
                        // Pitchbend: 3 bytes 0xEx Fine     [0,127] Coarse   [0,127] -> msb always 0
                        if(MidiEvent.size==3)
                        {
                            jack_midi_data_t TypeByte = MidiEvent.buffer[0] & 0xF0;
                            if(TypeByte==0x90)
                            {
                                m_MidiHandler->OnNoteOn(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                            }
                            else if(TypeByte==0x80)
                            {
                                m_MidiHandler->OnNoteOff(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                            }
                            else if(TypeByte==0xB0)
                            {
                                m_MidiHandler->OnController(MidiEvent.buffer[1], MidiEvent.buffer[2], MidiEvent.time);
                            }
                            else if(TypeByte==0xE0)
                            {
                                m_MidiHandler->OnPitchbend((MidiEvent.buffer[2]-64)<<7, MidiEvent.time);//fine?
                            }
                            else
                            {
                                m_MidiHandler->OnUnknown(MidiEvent.time);
                            }
                        }
                        else
                        {
                            m_MidiHandler->OnUnknown(MidiEvent.time);
                        }
                    }
                    ++EventIndex;
                }
            }

            // should return 0 upon succes, non-zero error code upon failure
            ReturnValue = 0;
        }
    }
    if(m_MidiOutputPort && m_MidiSource)
    {
        int NumConnected = jack_port_connected(m_MidiOutputPort);
        if(0<NumConnected)
        {
            void* DstBuffer = jack_port_get_buffer(m_MidiOutputPort, NumFrames);
            jack_midi_clear_buffer(DstBuffer);
            m_MidiSource->OnRead(DstBuffer, NumFrames, TimeStamp);
        }
    }
    // generating audio
    if(m_AudioOutputPort && m_AudioSource)
    {
        int NumConnected = jack_port_connected(m_AudioOutputPort);
        if(0<NumConnected)
        {
            void* DstBuffer = jack_port_get_buffer(m_AudioOutputPort, NumFrames);
            // should return 0 upon succes, non-zero error code upon failure
            ReturnValue = m_AudioSource->OnRead(DstBuffer, NumFrames, TimeStamp);
        }
    }
    // handle incoming audio
    if(m_AudioInputPort && m_AudioRenderer)
    {
        int NumConnected = jack_port_connected(m_AudioInputPort);
        if(0<NumConnected)
        {
            void* SrcBuffer = jack_port_get_buffer(m_AudioInputPort, NumFrames);
            // should return 0 upon succes, non-zero error code upon failure
            ReturnValue = m_AudioRenderer->OnWrite(SrcBuffer, NumFrames, TimeStamp);
        }
    }

    return ReturnValue;
}

void CJackIOManager::OnShutdown()
{
    std::cout << "JAck shutting down unexpectedly!" << std::endl;
    // not sure if we can do this inside this function!
    //Close();
}

bool CJackIOManager::ActivateClient()
{
    bool Success = false;
    if(m_Client)
    {
        // tell the JACK server that we are ready to roll
        if(0==jack_activate(m_Client))
        {
            Success = true;
        }
        else
        { // TODO capture error and print it?
            std::cerr << "cannot activate client" << std::endl;
        }
    }
    return Success;
}


