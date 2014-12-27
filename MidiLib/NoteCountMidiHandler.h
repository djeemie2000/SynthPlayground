#ifndef NOTECOUNTMIDIINPUTHANDLER_H
#define NOTECOUNTMIDIINPUTHANDLER_H

#include <memory>
#include "MidiHandlerI.h"

class CNoteCountMidiInputHandler : public IMidiHandler
{
public:
    CNoteCountMidiInputHandler(std::shared_ptr<IMidiHandler> Handler);

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    std::shared_ptr<IMidiHandler> m_Handler;
    int m_NoteCount;
};

#endif // NOTECOUNTMIDIINPUTHANDLER_H
