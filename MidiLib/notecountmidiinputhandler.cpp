#include "notecountmidiinputhandler.h"

CNoteCountMidiInputHandler::CNoteCountMidiInputHandler(std::shared_ptr<IMidiInputHandler> Handler)
 : m_Handler(Handler)
 , m_NoteCount(0)
{
}

void CNoteCountMidiInputHandler::OnNoteOn(int Note, int Velocity)
{
    ++m_NoteCount;
    m_Handler->OnNoteOn(Note, Velocity);
}

void CNoteCountMidiInputHandler::OnNoteOff(int Note, int Velocity)
{
    --m_NoteCount;
    if(m_NoteCount<=0)
    {
        m_Handler->OnNoteOff(Note, Velocity);
    }
}

void CNoteCountMidiInputHandler::OnController(int Parameter, int Value)
{
    m_Handler->OnController(Parameter, Value);
}

void CNoteCountMidiInputHandler::OnPitchbend(int Value)
{
    m_Handler->OnPitchbend(Value);
}

void CNoteCountMidiInputHandler::OnUnknown()
{
    m_Handler->OnUnknown();
}
