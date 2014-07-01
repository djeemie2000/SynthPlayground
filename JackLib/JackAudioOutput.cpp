//#include <functional>
#include <iostream>
#include "JackAudioOutput.h"
#include "AudioSource2I.h"

namespace
{

int JackProcessFunction(jack_nframes_t NumFrames, void* arg)
{
    return ((CJackIOManager*)arg)->OnProcessAudioOutput(NumFrames);
}

void JackShutdownFunction(void* arg)
{
    ((CJackIOManager*)arg)->CloseClient();
}

}

CJackIOManager::CJackIOManager()
 : m_Client(0)
 , m_SamplingFrequency(-1)
 , m_AudioOutputPort(0)
 , m_AudioSource()
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

        Success = true;
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
            // tell the JACK server to call `process()' whenever there is work to be done.
            if(0==jack_set_process_callback(m_Client,
                                            JackProcessFunction,
                                            this))
            {
                m_AudioSource = AudioSource;
                Success = true;
            }
            else
            {
                std::cerr << "Failed to set process callback for audio output " << Name << std::endl;
            }
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

int CJackIOManager::OnProcessAudioOutput(jack_nframes_t NumFrames)
{
    // if this function is called, it is fair to assume we are opened
    void* DstBuffer = jack_port_get_buffer(m_AudioOutputPort, NumFrames);
    // should return 0 upon succes, non-zero error code upon failure
    return m_AudioSource->OnRead(DstBuffer, NumFrames);
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


