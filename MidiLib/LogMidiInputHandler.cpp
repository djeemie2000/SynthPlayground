#include <iostream>
#include "LogMidiInputHandler.h"

CLogMidiInputHandler::CLogMidiInputHandler()
{
}

void CLogMidiInputHandler::OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp)
{
    std::cout << TimeStamp << " - Note on  : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp)
{
    std::cout <<TimeStamp << " - Note off : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnController(int Parameter, int Value, std::uint32_t TimeStamp)
{
    std::cout << TimeStamp << " - Control  : " << std::hex << "0x" << Parameter << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnPitchbend(int Value, std::uint32_t TimeStamp)
{
    std::cout << TimeStamp << " - Pitchbend: " << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnUnknown(std::uint32_t TimeStamp)
{
    std::cout << TimeStamp << " - Unknown midi event" << std::endl;
}
