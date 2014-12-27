#ifndef LOGMIDIINPUTHANDLER_H
#define LOGMIDIINPUTHANDLER_H

#include "MidiHandlerI.h"

class CLogMidiInputHandler : public IMidiHandler
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
