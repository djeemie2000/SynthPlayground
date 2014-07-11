#ifndef LOGMIDIINPUTHANDLER_H
#define LOGMIDIINPUTHANDLER_H

#include "MidiInputHandlerI.h"

class CLogMidiInputHandler : public IMidiInputHandler
{
public:
    CLogMidiInputHandler();

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;
};

#endif // LOGMIDIINPUTHANDLER_H
