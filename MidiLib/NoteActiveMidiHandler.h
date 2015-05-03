#ifndef CNOTEACTIVEMIDIHANDLER_H
#define CNOTEACTIVEMIDIHANDLER_H

#include <array>
#include "MidiHandlerI.h"

class CNoteActiveMidiHandler : public IMidiHandler
{
public:
    CNoteActiveMidiHandler();

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int /*Parameter*/, int /*Value*/, std::uint32_t /*TimeStamp*/) override {}
    void OnPitchbend(int /*Value*/, std::uint32_t /*TimeStamp*/) override {}
    void OnUnknown(std::uint32_t /*TimeStamp*/) override {}

    bool GetNoteActive(int MidiNote) const;

private:
    static constexpr int MinMidiNote = 0;
    static constexpr int MaxMidiNote = 127;
    static constexpr int MidiNoteRange = MaxMidiNote - MinMidiNote +1;
    std::array<bool, MidiNoteRange> m_MidiNoteActive;
};

#endif // CNOTEACTIVEMIDIHANDLER_H
