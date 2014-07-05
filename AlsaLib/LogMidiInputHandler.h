#ifndef LOGMIDIINPUTHANDLER_H
#define LOGMIDIINPUTHANDLER_H

#include "MidiInputHandlerI.h"

class CLogMidiInputHandler : public IMidiInputHandler
{
public:
    CLogMidiInputHandler();

    void OnNoteOn(int Note, int Velocity) override;
    void OnNoteOff(int Note, int Velocity) override;
    void OnController(int Parameter, int Value) override;
    void OnPitchbend(int Value) override;
    void OnUnknown() override;
};

#endif // LOGMIDIINPUTHANDLER_H
