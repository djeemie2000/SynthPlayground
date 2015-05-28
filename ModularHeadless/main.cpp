#include <iostream>
#include <string>
#include <thread>
#include <csignal>
#include "Pitch.h"
#include "ModularHeadlessController.h"

volatile std::sig_atomic_t gSignalStatus = 0;

void signal_handler(int Signal)
{
    gSignalStatus = Signal;
}

void Usage()
{
    std::cout << "Usage: exe Path" << std::endl;
}

int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
        std::signal(SIGILL, signal_handler);
        std::signal(SIGSEGV, signal_handler);
        std::signal(SIGFPE, signal_handler);
        std::signal(SIGABRT, signal_handler);

        // setup
        std::string Path(argv[1]);
        CModularHeadlessController Controller;
        Controller.Load(Path);

        std::cout << "Opened patch " << Path << std::endl;

        // detect ctrl-C or other signals
        while(gSignalStatus==0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "Captured signal " << gSignalStatus << std::endl;

        // cleanup
        return 0;
    }

    Usage();
	return -1;
}

