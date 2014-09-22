#include "notecountmidiinputhandler.h"

CNoteCountMidiInputHandler::CNoteCountMidiInputHandler(std::shared_ptr<IMidiHandler> Handler)
 : m_Handler(Handler)
 , m_NoteCount(0)
{
}

void CNoteCountMidiInputHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    ++m_NoteCount;
    m_Handler->OnNoteOn(Note, Velocity, TimeStamp);
}

void CNoteCountMidiInputHandler::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    --m_NoteCount;
    if(m_NoteCount<=0)
    {
        m_Handler->OnNoteOff(Note, Velocity, TimeStamp);
    }
}

void CNoteCountMidiInputHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    m_Handler->OnController(Parameter, Value, TimeStamp);
}

void CNoteCountMidiInputHandler::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    m_Handler->OnPitchbend(Value, TimeStamp);
}

void CNoteCountMidiInputHandler::OnUnknown(std::uint32_t TimeStamp)
{
    m_Handler->OnUnknown(TimeStamp);
}
