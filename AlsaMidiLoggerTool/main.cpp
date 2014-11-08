#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "AlsaMidiInput.h"
#include "LogMidiInputHandler.h"

using namespace std;

void About()
{
    std::cout << "------------------" << std::endl;
    std::cout << "AlsaMidiLoggerTool" << std::endl;
    std::cout << "------------------" << std::endl;
}

int main()
{
    About();

    CLogMidiInputHandler Handler;
    CAlsaMidiInput MidiInput(Handler);

    MidiInput.Open("AlsaMidiLoggerTool", "MidiIn");

    // wait untill keypressed
    char bs = std::getchar();

    MidiInput.Close();

    About();

    return 0;
}

