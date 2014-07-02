#ifndef JACKAUDIOOUTPUT_H
#define JACKAUDIOOUTPUT_H

#include <string>
#include <memory>
#include<jack/jack.h>

class IAudioSource2;

/*!
 * \brief The CJackAudioOutput class
 * Usage:
 * OpenClient,
 * then open some audio/midi outputs/inputs,
 * then activate client
 * CloseClient
 */
class CJackIOManager
{
public:
    CJackIOManager();
    ~CJackIOManager();

    bool OpenClient(const std::string& ClientName);
    int SamplingFrequency() const;
    bool ClientIsOpen() const;

    bool OpenAudioOutput(const std::string& Name, std::shared_ptr<IAudioSource2> AudioSource);
    //bool OpenAudioInput(const std::string& Name, std::shared_ptr<IAudioRenderer2> AudioSink);
    // idem for midi -> midi handler => generic midi stuff into MidiLib => AlsaLib separately

    bool ActivateClient();

    void CloseClient();// close client and all ports (audio input/output,midi)

    int OnProcessAudioOutput(jack_nframes_t NumFrames);
    void OnShutdown();

private:
    jack_client_t*  m_Client;
    jack_nframes_t  m_SamplingFrequency;
    jack_port_t *   m_AudioOutputPort;
    std::shared_ptr<IAudioSource2>   m_AudioSource;
};

#endif // JACKAUDIOOUTPUT_H
