#include <iostream>
#include "LogMidiInputHandler.h"

CLogMidiInputHandler::CLogMidiInputHandler()
{
}

void CLogMidiInputHandler::OnNoteOn(int Note, int Velocity)
{
    std::cout << "Note on  : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnNoteOff(int Note, int Velocity)
{
    std::cout << "Note off : " << std::hex << "0x" << Note << " vel(" << std::dec << Velocity << ")" << std::endl;
}

void CLogMidiInputHandler::OnController(int Parameter, int Value)
{
    std::cout << "Control  : " << std::hex << "0x" << Parameter << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnPitchbend(int Value)
{
    std::cout << "Pitchbend: " << " val(" << std::dec << Value << ")" << std::endl;
}

void CLogMidiInputHandler::OnUnknown()
{
    std::cout << "Unknown midi event" << std::endl;
}
