#ifndef NOTECOUNTMIDIINPUTHANDLER_H
#define NOTECOUNTMIDIINPUTHANDLER_H

#include <memory>
#include "MidiInputHandlerI.h"

class CNoteCountMidiInputHandler : public IMidiInputHandler
{
public:
    CNoteCountMidiInputHandler(std::shared_ptr<IMidiInputHandler> Handler);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    std::shared_ptr<IMidiInputHandler> m_Handler;
    int m_NoteCount;
};

#endif // NOTECOUNTMIDIINPUTHANDLER_H
