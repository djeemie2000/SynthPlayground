#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include <string>
#include <alsa/asoundlib.h>

class IMidiInputHandler;

class CMidiInput
{
public:
    CMidiInput(IMidiInputHandler& Handler);
    ~CMidiInput();

    bool OpenMidiInput(const std::string &ClientName, const std::string &PortName);
    bool CloseMidiInput();

    void Start();
    void Stop();
    void Run();

private:
    IMidiInputHandler& m_Handler;
    snd_seq_event_t *ReadMidiEvent() const;
    void ProcessMidiEvent(const snd_seq_event_t *ev);

    snd_seq_t*  m_MidiSequencerHandle;
    int         m_MidiInputPort;
};


#endif // MIDIINPUT_H
