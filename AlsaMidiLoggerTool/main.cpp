#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <csignal>
#include "AlsaMidiInput.h"
#include "LogMidiInputHandler.h"

using namespace std;

volatile std::sig_atomic_t gSignalStatus = 0;

void signal_handler(int Signal)
{
    gSignalStatus = Signal;
}

void About()
{
    std::cout << "------------------" << std::endl;
    std::cout << "AlsaMidiLoggerTool" << std::endl;
    std::cout << "------------------" << std::endl;
}

int main()
{
    About();

    // setup
    CLogMidiInputHandler Handler;
    CAlsaMidiInput MidiInput(Handler);

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGILL, signal_handler);
    std::signal(SIGSEGV, signal_handler);
    std::signal(SIGFPE, signal_handler);
    std::signal(SIGABRT, signal_handler);

    // Run
    MidiInput.Open("AlsaMidiLoggerTool", "MidiIn");

    // detect ctrl-C or other signals
    while(gSignalStatus==0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "Captured signal " << gSignalStatus << std::endl;

    // cleanup
    MidiInput.Close();

    About();

    return 0;
}

