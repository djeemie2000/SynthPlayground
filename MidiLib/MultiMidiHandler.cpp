#include "MultiMidiHandler.h"

CMultiMidiHandler::CMultiMidiHandler()
 : m_Handlers()
{
}

void CMultiMidiHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->OnNoteOn(Note, Velocity, TimeStamp);
    }
}

void CMultiMidiHandler::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->OnNoteOff(Note, Velocity, TimeStamp);
    }
}

void CMultiMidiHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->OnController(Parameter, Value, TimeStamp);
    }
}

void CMultiMidiHandler::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->OnPitchbend(Value, TimeStamp);
    }
}

void CMultiMidiHandler::OnUnknown(std::uint32_t TimeStamp)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->OnUnknown(TimeStamp);
    }
}

void CMultiMidiHandler::AddHandler(std::shared_ptr<IMidiHandler> Handler)
{
    m_Handlers.push_back(Handler);
}
