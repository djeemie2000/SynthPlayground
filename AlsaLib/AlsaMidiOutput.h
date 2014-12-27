#pragma once

#include <string>
#include <memory>
#include <alsa/asoundlib.h>
#include "MidiHandlerI.h"

class CAlsaMidiOutput : public IMidiHandler
{
public:
    CAlsaMidiOutput();
    ~CAlsaMidiOutput();

    bool Open(const std::string &ClientName, const std::string &PortName);
    void Close();

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    bool OpenMidiOutput(const std::string &ClientName, const std::string &PortName);
    bool CloseMidiOutput();

    void WriteMidiEvent(snd_seq_event_t &ev);

    snd_seq_t*  m_MidiSequencerHandle;
    int         m_MidiOutputPort;
    bool        m_IsOpen;
};
