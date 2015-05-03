#include "NoteActiveMidiHandler.h"

CNoteActiveMidiHandler::CNoteActiveMidiHandler()
 : m_MidiNoteActive()
{
    m_MidiNoteActive.fill(false);
}

void CNoteActiveMidiHandler::OnNoteOn(int Note, int /*Velocity*/, uint32_t /*TimeStamp*/)
{
    if(MinMidiNote<=Note && Note<=MaxMidiNote)
    {
        m_MidiNoteActive[Note] = true;
        // TODO sample accurate
    }
}

void CNoteActiveMidiHandler::OnNoteOff(int Note, int /*Velocity*/, uint32_t /*TimeStamp*/)
{
    if(MinMidiNote<=Note && Note<=MaxMidiNote)
    {
        m_MidiNoteActive[Note] = false;
        // TODO sample accurate
    }
}

bool CNoteActiveMidiHandler::GetNoteActive(int MidiNote) const
{
    return MinMidiNote<=MidiNote && MidiNote<=MaxMidiNote && m_MidiNoteActive[MidiNote];
}


