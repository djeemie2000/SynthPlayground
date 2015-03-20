#ifndef JACKAUDIOOUTPUT_H
#define JACKAUDIOOUTPUT_H

#include <string>
#include <memory>
#include <vector>
#include "JackWin32Port.h"
#include <jack/jack.h>

class IAudioRenderer;
class IMidiHandler;
class IMidiSource;
class IAudioFilter;

/*!
 * \brief The CJackIOManager class
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

    bool OpenAudioInput(const std::string& Name, std::shared_ptr<IAudioRenderer> AudioRenderer);
    // idem for midi -> midi handler => generic midi stuff into MidiLib => MidiLib separately
    bool OpenMidiInput(const std::string& Name, std::shared_ptr<IMidiHandler> MidiHandler);
    bool OpenMidiOutput(const std::string& Name, std::shared_ptr<IMidiSource> MidiSource);
    bool OpenAudioFilter(std::shared_ptr<IAudioFilter> AudioFilter);

    bool ActivateClient();

    void CloseClient();// close client and all ports (audio input/output,midi)

    int OnProcess(jack_nframes_t NumFrames);
    void OnShutdown();

private:
    jack_client_t*  m_Client;
    jack_nframes_t  m_SamplingFrequency;

    jack_port_t*    m_AudioInputPort;
    std::shared_ptr<IAudioRenderer> m_AudioRenderer;

    jack_port_t*    m_MidiInputPort;
    std::shared_ptr<IMidiHandler> m_MidiHandler;

    jack_port_t*    m_MidiOutputPort;
    std::shared_ptr<IMidiSource> m_MidiSource;

    struct SAudioFilter
    {
        std::vector<jack_port_t*> s_InputPorts;
        std::vector<jack_port_t*> s_OutputPorts;
        std::vector<jack_port_t*> s_MidiInputPorts;
        std::vector<jack_port_t*> s_MidiOutputPorts;
        std::shared_ptr<IAudioFilter> s_Filter;
    };

    SAudioFilter m_AudioFilter;
};

#endif // JACKAUDIOOUTPUT_H
