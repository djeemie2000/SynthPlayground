#ifndef NOTECOUNTMIDIINPUTHANDLER_H
#define NOTECOUNTMIDIINPUTHANDLER_H

#include "MidiInputHandlerI.h"

class CNoteCountMidiInputHandler : public IMidiInputHandler
{
public:
    CNoteCountMidiInputHandler(IMidiInputHandler& Handler);

    void OnNoteOn(int Note, int Velocity) override;
    void OnNoteOff(int Note, int Velocity) override;
    void OnController(int Parameter, int Value) override;
    void OnPitchbend(int Value) override;
    void OnUnknown() override;

private:
    IMidiInputHandler& m_Handler;
    int m_NoteCount;
};

#endif // NOTECOUNTMIDIINPUTHANDLER_H
