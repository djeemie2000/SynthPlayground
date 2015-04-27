#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <csignal>
#include "MidiLoggerModule.h"

using namespace std;

volatile std::sig_atomic_t gSignalStatus = 0;

void signal_handler(int Signal)
{
    gSignalStatus = Signal;
}

void About()
{
    std::cout << "------------------" << std::endl;
    std::cout << "JackMidiLoggerTool" << std::endl;
    std::cout << "------------------" << std::endl;
}

int main()
{
    About();

    // setup
    CMidiLoggerModule Module("MidiLoggerTool");

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGILL, signal_handler);
    std::signal(SIGSEGV, signal_handler);
    std::signal(SIGFPE, signal_handler);
    std::signal(SIGABRT, signal_handler);

    // detect ctrl-C or other signals
    while(gSignalStatus==0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "Captured signal " << gSignalStatus << std::endl;

    // cleanup
    About();

    return 0;
}

