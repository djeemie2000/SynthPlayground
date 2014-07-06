#include "MidiInputController.h"
#include "notecountmidiinputhandler.h"
#include "CommandStackMidiInputHandler.h"
#include "LogMidiInputHandler.h"

CMidiInputController::CMidiInputController(CCommandStackController &CommandStackController)
 : m_MidiInputLogger(new CLogMidiInputHandler())
{
    std::shared_ptr<CCommandStackMidiInputHandler> CommandStackMidiInputHandler(new CCommandStackMidiInputHandler(CommandStackController));

    m_MidiControllerHandler = CommandStackMidiInputHandler;
    m_MidiInputHandler.reset(new CNoteCountMidiInputHandler(CommandStackMidiInputHandler));
}

void CMidiInputController::OnNoteOn(int Note, int Velocity)
{
    m_MidiInputHandler->OnNoteOn(Note, Velocity);
    m_MidiInputLogger->OnNoteOn(Note, Velocity);
}

void CMidiInputController::OnNoteOff(int Note, int Velocity)
{
    m_MidiInputHandler->OnNoteOff(Note, Velocity);
    m_MidiInputLogger->OnNoteOff(Note, Velocity);
}

void CMidiInputController::OnController(int Parameter, int Value)
{
    m_MidiInputHandler->OnController(Parameter, Value);
    m_MidiInputLogger->OnController(Parameter, Value);
}

void CMidiInputController::OnPitchbend(int Value)
{
    m_MidiInputHandler->OnPitchbend(Value);
    m_MidiInputLogger->OnPitchbend(Value);
}

void CMidiInputController::OnUnknown()
{
    m_MidiInputHandler->OnUnknown();
    m_MidiInputLogger->OnUnknown();
}

bool CMidiInputController::Link(const std::string &ParameterName, int Parameter)
{
    return m_MidiControllerHandler->Link(ParameterName, Parameter);
}

void CMidiInputController::Add(const std::string &ParameterName, const IMidiControllerHandler::HandlerFunction &Handler)
{
    m_MidiControllerHandler->Add(ParameterName, Handler);
}

