#ifndef JACKAUDIOOUTPUT_H
#define JACKAUDIOOUTPUT_H

#include <string>
#include<jack/jack.h>

class IAudioSource2;

class CJackAudioOutput
{
public:
    CJackAudioOutput(IAudioSource2& AudioSource);
    ~CJackAudioOutput();

    bool Open(const std::string& ClientName, const std::string& PortName);
    void Close();

    bool IsOpen() const;
    int SamplingFrequency() const;


    int OnProcess(jack_nframes_t NumFrames);
    void OnShutdown();

private:
    IAudioSource2&   m_AudioSource;
    jack_client_t*  m_Client;
    jack_port_t *   m_Port;
    jack_nframes_t  m_SamplingFrequency;
};

#endif // JACKAUDIOOUTPUT_H
