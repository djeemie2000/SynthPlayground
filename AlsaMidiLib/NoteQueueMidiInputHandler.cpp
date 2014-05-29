#include "NoteQueueMidiInputHandler.h"

CNoteQueueMidiInputHandler::CNoteQueueMidiInputHandler(IMidiInputHandler &Handler)
 : m_Handler(Handler)
 , m_NoteQueue()
{
}

void CNoteQueueMidiInputHandler::OnNoteOn(int Note, int Velocity)
{
    m_NoteQueue.push_back({Note, Velocity});
    m_Handler.OnNoteOn(Note, Velocity);
}

void CNoteQueueMidiInputHandler::OnNoteOff(int Note, int Velocity)
{
    SQueueItem QueueItem(Note, Velocity);
    m_NoteQueue.remove(QueueItem);
    if(m_NoteQueue.empty())
    {
        m_Handler.OnNoteOff(Note, Velocity);
    }
    else if(m_NoteQueue.back()!=QueueItem)
    {
        m_Handler.OnNoteOn(m_NoteQueue.back().s_Note, m_NoteQueue.back().s_Velocity);
    }
}

void CNoteQueueMidiInputHandler::OnController(int Parameter, int Value)
{
    m_Handler.OnController(Parameter, Value);
}

void CNoteQueueMidiInputHandler::OnPitchbend(int Value)
{
    m_Handler.OnPitchbend(Value);
}

void CNoteQueueMidiInputHandler::OnUnknown()
{
    m_Handler.OnUnknown();
}

CNoteQueueMidiInputHandler::SQueueItem::SQueueItem(int Note, int Velocity)
 : s_Note(Note)
 , s_Velocity(Velocity)
{
}

bool CNoteQueueMidiInputHandler::SQueueItem::operator ==(const CNoteQueueMidiInputHandler::SQueueItem &Other) const
{
    return s_Note == Other.s_Note;
}

bool CNoteQueueMidiInputHandler::SQueueItem::operator !=(const CNoteQueueMidiInputHandler::SQueueItem &Other) const
{
    return s_Note != Other.s_Note;
}
