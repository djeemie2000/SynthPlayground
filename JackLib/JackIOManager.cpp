#include <iostream>
#include "JackIOManager.h"
#include "AudioSource2I.h"
#include "AudioRendererI.h"

namespace
{

int JackProcessFunction(jack_nframes_t NumFrames, void* arg)
{
    return ((CJackIOManager*)arg)->OnProcessAudio(NumFrames);
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

int CJackIOManager::OnProcessAudio(jack_nframes_t NumFrames)
{
    // if this function is called, it is fair to assume we are opened
    int ReturnValue = 0;
    if(m_AudioOutputPort && m_AudioSource)
    {
        int NumConnected = jack_port_connected(m_AudioOutputPort);
        if(0<NumConnected)
        {
            void* DstBuffer = jack_port_get_buffer(m_AudioOutputPort, NumFrames);
            // should return 0 upon succes, non-zero error code upon failure
            ReturnValue = m_AudioSource->OnRead(DstBuffer, NumFrames);
        }
    }
    if(m_AudioInputPort && m_AudioRenderer)
    {
        int NumConnected = jack_port_connected(m_AudioInputPort);
        if(0<NumConnected)
        {
            void* SrcBuffer = jack_port_get_buffer(m_AudioInputPort, NumFrames);
            // should return 0 upon succes, non-zero error code upon failure
            ReturnValue = m_AudioRenderer->OnWrite(SrcBuffer, NumFrames);
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


