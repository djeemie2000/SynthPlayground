#include "CommandStackMidiInputHandler.h"
#include "CommandStackController.h"
#include "CommandStack.h"

CCommandStackMidiInputHandler::CCommandStackMidiInputHandler(CCommandStackController &CommandStackHandler)
 : m_CommandStackHandler(CommandStackHandler)
{
}

void CCommandStackMidiInputHandler::OnNoteOn(int Note, int Velocity)
{
    // handled by a 'custom' command
    // Midi notes are in [0x00, 0x77] range
    m_CommandStackHandler.Handle({"Midi/NoteOn", false, Note | Velocity<<8, 0.0f });
}

void CCommandStackMidiInputHandler::OnNoteOff(int Note, int Velocity)
{
    // handled by a 'custom' command
    // Midi notes are in [0x00, 0x77] range
    m_CommandStackHandler.Handle({"Midi/NoteOff", false, Note | Velocity<<8, 0.0f });
}

void CCommandStackMidiInputHandler::OnController(int Parameter, int Value)
{
    auto itLink = m_Links.find(Parameter);
    if(itLink != m_Links.end())
    {
        auto itHandler = m_Handlers.find(itLink->second);
        if(itHandler!=m_Handlers.end())
        {
            SCmdStackItem Item;
            Item.s_Name = itHandler->first;
            itHandler->second(Item, Value);
            m_CommandStackHandler.Handle(Item);
        }
    }
}

void CCommandStackMidiInputHandler::OnPitchbend(int Value)
{
    // handle by 'custom' command
    // m_CommandStackHandler.Handle({"Midi/PitchBend", false, Value, 0.0f });
    // TODO use dedicated midi controller number
}

void CCommandStackMidiInputHandler::OnUnknown()
{
    //not handled
}

bool CCommandStackMidiInputHandler::Link(const string &ParameterName, int Parameter)
{
    m_Links[Parameter] = ParameterName;
    return true;
}

void CCommandStackMidiInputHandler::Add(const string &ParameterName, const CCommandStackMidiInputHandler::HandlerFunction &Handler)
{
    m_Handlers[ParameterName] = Handler;
}

