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

void CMidiInputController::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    m_MidiInputHandler->OnNoteOn(Note, Velocity, TimeStamp);
    m_MidiInputLogger->OnNoteOn(Note, Velocity, TimeStamp);
}

void CMidiInputController::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    m_MidiInputHandler->OnNoteOff(Note, Velocity, TimeStamp);
    m_MidiInputLogger->OnNoteOff(Note, Velocity, TimeStamp);
}

void CMidiInputController::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    m_MidiInputHandler->OnController(Parameter, Value, TimeStamp);
    m_MidiInputLogger->OnController(Parameter, Value, TimeStamp);
}

void CMidiInputController::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    m_MidiInputHandler->OnPitchbend(Value, TimeStamp);
    m_MidiInputLogger->OnPitchbend(Value, TimeStamp);
}

void CMidiInputController::OnUnknown(std::uint32_t TimeStamp)
{
    m_MidiInputHandler->OnUnknown(TimeStamp);
    m_MidiInputLogger->OnUnknown(TimeStamp);
}

bool CMidiInputController::Link(const std::string &ParameterName, int Parameter)
{
    return m_MidiControllerHandler->Link(ParameterName, Parameter);
}

void CMidiInputController::Add(const std::string &ParameterName, const IMidiControllerHandler::HandlerFunction &Handler)
{
    m_MidiControllerHandler->Add(ParameterName, Handler);
}

