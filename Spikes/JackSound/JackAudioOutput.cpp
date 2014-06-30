#include <functional>
#include "JackAudioOutput.h"
#include "AudioSource2I.h"

namespace
{

int JackProcessFunction(jack_nframes_t NumFrames, void* arg)
{
    return ((CJackAudioOutput*)arg)->OnProcess(NumFrames);
}

void JackShutdownFunction(void* arg)
{
    ((CJackAudioOutput*)arg)->Close();
}

}

CJackAudioOutput::CJackAudioOutput(IAudioSource2& AudioSource)
 : m_AudioSource(AudioSource)
 , m_Client(0)
 , m_Port(0)
 , m_SamplingFrequency(44100)
{
}

CJackAudioOutput::~CJackAudioOutput()
{
    Close();
}

bool CJackAudioOutput::Open(const std::string &ClientName, const std::string &PortName)
{
    bool Success = false;
    // open client with requested name. No further options are needed
    m_Client = jack_client_open(ClientName.c_str(), JackNullOption, 0);
    if(m_Client)
    {
        // retrieve and display the current sample rate.
        m_SamplingFrequency = jack_get_sample_rate(m_Client);
        //printf("engine sample rate: %d \n", m_SamplingFrequency);

        // create one output port. Use default audio type, which is mono float 32 bits.
        // it is adviced to use 'terminal' option for audio synthesizers.
        m_Port = jack_port_register(m_Client, PortName.c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput|JackPortIsTerminal, 0);
        if(m_Port)
        {
            // tell the JACK server to call `process()' whenever there is work to be done.
            jack_set_process_callback(m_Client,
                                      JackProcessFunction,
                                      this);

            // tell the JACK server to call `jack_shutdown()' if it ever shuts down,
            // either entirely, or if it just decides to stop calling us.
            jack_on_shutdown(m_Client,
                             JackShutdownFunction,
                             this);

            // tell the JACK server that we are ready to roll
            if(0==jack_activate(m_Client))
            {
                Success = true;
            }
            else
            { // TODO capture error and print it?
                fprintf(stderr, "cannot activate client\r\n");
            }
        }
    }
    if(!Success)
    {
        // make sure everything is cleaned ip, even if just one step failed
        Close();
    }

    return Success;
}

void CJackAudioOutput::Close()
{
    if(m_Client)
    {
        if(m_Port)
        {
            jack_port_unregister(m_Client, m_Port);
            m_Port = 0;
        }
        // tell jack we do not want to play along anymore
        jack_deactivate(m_Client);
        // close and remove the client
        jack_client_close(m_Client);
        // make sure we know we are closed
        m_Client = 0;
    }
}

bool CJackAudioOutput::IsOpen() const
{
    return 0!=m_Client;
}

int CJackAudioOutput::SamplingFrequency() const
{
    return static_cast<int>(m_SamplingFrequency);
}

int CJackAudioOutput::OnProcess(jack_nframes_t NumFrames)
{
    // if this function is called, it is fair to assume we are opened
    void* DstBuffer = jack_port_get_buffer(m_Port, NumFrames);
    // should return 0 upon succes, non-zero error code upon failure
    return m_AudioSource.OnRead(DstBuffer, NumFrames);
}

void CJackAudioOutput::OnShutdown()
{
    // not sure if we can do this inside this function!
    Close();
}


