#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include <string>
#include <memory>
#include <alsa/asoundlib.h>

class IMidiHandler;
template<class T> class CPeriodicThreadRunner;

class CAlsaMidiInput
{
public:
    CAlsaMidiInput(IMidiHandler& Handler);
    ~CAlsaMidiInput();

    bool Open(const std::string &ClientName, const std::string &PortName);
    void Close();

    void OnTick();

private:
    bool OpenMidiInput(const std::string &ClientName, const std::string &PortName);
    bool CloseMidiInput();
    void StartListening();
    void StopListening();

    IMidiHandler& m_Handler;
    snd_seq_event_t *ReadMidiEvent(int& RemainingBufferSize) const;
    void ProcessMidiEvent(const snd_seq_event_t *ev);

    snd_seq_t*  m_MidiSequencerHandle;
    int         m_MidiInputPort;
    bool        m_IsOpen;
    std::unique_ptr<CPeriodicThreadRunner<CAlsaMidiInput>> m_ThreadRunner;
};


#endif // MIDIINPUT_H
