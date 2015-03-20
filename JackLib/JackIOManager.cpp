#include <iostream>
#include "JackIOManager.h"
#include "AudioRendererI.h"
#include "MidiHandlerI.h"
#include "MidiSourceI.h"
#include "AudioFilterI.h"
#include <jack/midiport.h>
#include "JackMidiRenderer.h"
#include "JackMidiHandler.h"

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
 , m_AudioInputPort(0)
 , m_AudioRenderer()
 , m_MidiInputPort(0)
 , m_MidiHandler()
 , m_MidiOutputPort(0)
 , m_MidiSource()
 , m_AudioFilter()
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

bool CJackIOManager::OpenMidiInput(const std::string &Name, std::shared_ptr<IMidiHandler> MidiHandler)
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

bool CJackIOManager::OpenAudioFilter(std::shared_ptr<IAudioFilter> AudioFilter)
{
    bool Success = false;
    if(m_Client && AudioFilter)
    {
        // TODO fail and reset filter struct if any port fails to create
        for(auto InputName : AudioFilter->GetInputNames())
        {
            jack_port_t* InputPort = jack_port_register(m_Client, InputName.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);//do not use JackPortIsTerminal unless only ins or only outs
            m_AudioFilter.s_InputPorts.push_back(InputPort);
        }
        for(auto OutputName : AudioFilter->GetOutputNames())
        {
            jack_port_t* OutputPort = jack_port_register(m_Client, OutputName.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);//do not use JackPortIsTerminal unless only ins or only outs
            m_AudioFilter.s_OutputPorts.push_back(OutputPort);
        }
        for(auto InputName : AudioFilter->GetMidiInputNames())
        {
            jack_port_t* InputPort = jack_port_register(m_Client, InputName.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);//use JackPortIsTerminal ?
            m_AudioFilter.s_MidiInputPorts.push_back(InputPort);
        }
        for(auto OutputName : AudioFilter->GetMidiOutputNames())
        {
            jack_port_t* OutputPort = jack_port_register(m_Client, OutputName.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);//use JackPortIsTerminal ?
            m_AudioFilter.s_MidiOutputPorts.push_back(OutputPort);
        }
        m_AudioFilter.s_Filter = AudioFilter;
        Success = true;
    }
    return Success;
}

void CJackIOManager::CloseClient()
{
    if(m_Client)
    {
        // audio in
        if(m_AudioInputPort)
        {
            jack_port_unregister(m_Client, m_AudioInputPort);
            m_AudioInputPort = 0;
        }
        m_AudioRenderer.reset();
        // midi in
        if(m_MidiInputPort)
        {
            jack_port_unregister(m_Client, m_MidiInputPort);
            m_MidiInputPort = 0;
        }
        m_MidiHandler.reset();
        // midi out
        if(m_MidiOutputPort)
        {
            jack_port_unregister(m_Client, m_MidiOutputPort);
            m_MidiOutputPort = 0;
        }
        m_MidiSource.reset();
        // filter
        for(auto& InputPort : m_AudioFilter.s_InputPorts)
        {
            jack_port_unregister(m_Client, InputPort);
            InputPort = 0;
        }
        m_AudioFilter.s_InputPorts.clear();
        for(auto& OutputPort : m_AudioFilter.s_OutputPorts)
        {
            jack_port_unregister(m_Client, OutputPort);
            OutputPort = 0;
        }
        m_AudioFilter.s_OutputPorts.clear();
        for(auto& MidiInputPort : m_AudioFilter.s_MidiInputPorts)
        {
            jack_port_unregister(m_Client, MidiInputPort);
            MidiInputPort = 0;
        }
        m_AudioFilter.s_MidiInputPorts.clear();
        for(auto& MidiOutputPort : m_AudioFilter.s_MidiOutputPorts)
        {
            jack_port_unregister(m_Client, MidiOutputPort);
            MidiOutputPort = 0;
        }
        m_AudioFilter.s_MidiOutputPorts.clear();
        m_AudioFilter.s_Filter.reset();

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
            CJackMidiRenderer(SrcBuffer).Accept(*m_MidiHandler);

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
    // audio filter
    if(m_AudioFilter.s_Filter)
    {
        // if nothing is connected => ignored (for now)
        std::vector<void*> SourceBuffers;
        for(auto& InputPort : m_AudioFilter.s_InputPorts)
        {
            int NumConnected = jack_port_connected(InputPort);
            void* SrcBuffer = jack_port_get_buffer(InputPort, NumFrames);
            SourceBuffers.push_back(0<NumConnected ? SrcBuffer : 0);
        }
        std::vector<void*> DestinationBuffers;
        for(auto& OutputPort : m_AudioFilter.s_OutputPorts)
        {
            int NumConnected = jack_port_connected(OutputPort);
            void* DstBuffer = jack_port_get_buffer(OutputPort, NumFrames);
            DestinationBuffers.push_back(0<NumConnected ? DstBuffer : 0);
        }
        std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers;
        for(auto& MidiInputPort : m_AudioFilter.s_MidiInputPorts)
        {
            void* SrcBuffer = jack_port_get_buffer(MidiInputPort, NumFrames);
            MidiRenderers.push_back(std::shared_ptr<IMidiRenderer>(new CJackMidiRenderer(SrcBuffer)));
        }
        std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers;
        for(auto& MidiOutputPort : m_AudioFilter.s_MidiOutputPorts)
        {
            void* DstBuffer = jack_port_get_buffer(MidiOutputPort, NumFrames);
            MidiHandlers.push_back(std::shared_ptr<IMidiHandler>(new CJackMidiHandler(DstBuffer)));
        }
        // should return 0 upon succes, non-zero error code upon failure
        ReturnValue = m_AudioFilter.s_Filter->OnProcess(SourceBuffers, DestinationBuffers, MidiRenderers, MidiHandlers, NumFrames, TimeStamp);
    }

    return ReturnValue;
}

void CJackIOManager::OnShutdown()
{
    std::cout << "Jack shutting down unexpectedly!" << std::endl;
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
