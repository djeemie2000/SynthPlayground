#include "NoteQueueMidiInputHandler.h"

CNoteQueueMidiInputHandler::CNoteQueueMidiInputHandler(std::shared_ptr<IMidiHandler> Handler)
 : m_Handler(Handler)
 , m_NoteQueue()
{
}

void CNoteQueueMidiInputHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    m_NoteQueue.push_back({Note, Velocity, TimeStamp});
    m_Handler->OnNoteOn(Note, Velocity, TimeStamp);
}

void CNoteQueueMidiInputHandler::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    SQueueItem QueueItem(Note, Velocity, TimeStamp);
    m_NoteQueue.remove(QueueItem);
    if(m_NoteQueue.empty())
    {
        m_Handler->OnNoteOff(Note, Velocity, TimeStamp);
    }
    else if(m_NoteQueue.back()!=QueueItem)
    {
        m_Handler->OnNoteOn(m_NoteQueue.back().s_Note, m_NoteQueue.back().s_Velocity, m_NoteQueue.back().s_TimeStamp);
    }
}

void CNoteQueueMidiInputHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    m_Handler->OnController(Parameter, Value, TimeStamp);
}

void CNoteQueueMidiInputHandler::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    m_Handler->OnPitchbend(Value, TimeStamp);
}

void CNoteQueueMidiInputHandler::OnUnknown(std::uint32_t TimeStamp)
{
    m_Handler->OnUnknown(TimeStamp);
}

CNoteQueueMidiInputHandler::SQueueItem::SQueueItem(int Note, int Velocity, std::uint32_t TimeStamp)
 : s_Note(Note)
 , s_Velocity(Velocity)
 , s_TimeStamp(TimeStamp)
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
