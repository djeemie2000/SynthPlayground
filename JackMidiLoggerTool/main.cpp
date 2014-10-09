#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "MidiLoggerModule.h"

using namespace std;

void About()
{
    std::cout << "------------------" << std::endl;
    std::cout << "JackMidiLoggerTool" << std::endl;
    std::cout << "------------------" << std::endl;
}

int main()
{
    About();

    CMidiLoggerModule Module("MidiLoggerTool");

    // wait untill keypressed
    char bs = std::getchar();

    std::cout << "------------------" << std::endl;
    std::cout << "JackMidiLoggerTool" << std::endl;
    std::cout << "------------------" << std::endl;

    return 0;
}

