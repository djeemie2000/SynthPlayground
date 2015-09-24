#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <csignal>
#include "AlsaMidiInput.h"
#include "MidiHandlerI.h"
#include "LinuxSerialPort.h"
#include "MultiMidiHandler.h"
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
    std::cout << "Alsa2SerialMidiTool" << std::endl;
    std::cout << "------------------" << std::endl;
}

std::string ParsePort(int argc, const char* argv[])
{
    std::string Port = "/dev/ttyACM0";
    if(2<=argc)
    {
        Port = argv[1];
    }
    return Port;
}

int ParseBaudrate(int argc, const char* argv[])
{
    int Baudrate = 9600;
    if(3<=argc)
    {
        Baudrate = std::stoi(argv[2]);//TODO try catch
    }
    return Baudrate;
}

bool ParseVerbose(int argc, const char* argv[])
{
    bool Verbose = true;
    if(4<=argc)
    {
        Verbose = (0!=std::stoi(argv[3]));//TODO try catch
    }
    return Verbose;
}

class CSerialMidiHandler : public IMidiHandler
{
public:
    CSerialMidiHandler();

    bool Open(const std::string& SerialPort, int SerialBaudrate);
    void Close();

    void OnNoteOn(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnNoteOff(int Note, int Velocity, std::uint32_t TimeStamp) override;
    void OnController(int Parameter, int Value, std::uint32_t TimeStamp) override;
    void OnPitchbend(int Value, std::uint32_t TimeStamp) override;
    void OnUnknown(std::uint32_t TimeStamp) override;

private:
    CLinuxSerialPort m_SerialPort;
};

CSerialMidiHandler::CSerialMidiHandler()
 : m_SerialPort()
{
}

bool CSerialMidiHandler::Open(const string &SerialPort, int SerialBaudrate)
{
    bool IsOpen = false;
    std::cout << "Opening serial port " << SerialPort << " (" << SerialBaudrate << ")" << std::endl;
    if(m_SerialPort.Open(SerialPort, SerialBaudrate, 0))
    {
        IsOpen = true;
    }
    else
    {
        std::cout << "failed!" << std::endl;
    }
    return IsOpen;
}

void CSerialMidiHandler::Close()
{
    std::cout << "Closing serial port" << std::endl;
    m_SerialPort.Close();
}

void CSerialMidiHandler::OnNoteOn(int Note, int Velocity, uint32_t /*TimeStamp*/)
{
    // Channel = 0 = omni?
    m_SerialPort.Write({ 0x90, static_cast<uint8_t>(Note), static_cast<uint8_t>(Velocity) });
}

void CSerialMidiHandler::OnNoteOff(int Note, int Velocity, uint32_t /*TimeStamp*/)
{
    // Channel = 0 = omni?
    m_SerialPort.Write({ 0x80, static_cast<uint8_t>(Note), static_cast<uint8_t>(Velocity) });
}

void CSerialMidiHandler::OnController(int Parameter, int Value, uint32_t /*TimeStamp*/)
{
    // Channel = 0 = omni?
    m_SerialPort.Write({ 0xB0, static_cast<uint8_t>(Parameter), static_cast<uint8_t>(Value) });
}

void CSerialMidiHandler::OnPitchbend(int Value, uint32_t /*TimeStamp*/)
{
    // Channel = 0 = omni?
    m_SerialPort.Write({ 0xE0, static_cast<uint8_t>(0), static_cast<uint8_t>(Value) });
}

void CSerialMidiHandler::OnUnknown(uint32_t /*TimeStamp*/)
{
}


int main(int argc, const char* argv[])
{
    About();

    // setup
    std::string Port = ParsePort(argc, argv);
    int Baudrate = ParseBaudrate(argc, argv);
    bool Verbose = ParseVerbose(argc, argv);

    CMultiMidiHandler MultiHandler;

    std::shared_ptr<CSerialMidiHandler> SerialHandler(new CSerialMidiHandler());
    SerialHandler->Open(Port, Baudrate);
    MultiHandler.AddHandler(SerialHandler);

    if(Verbose)
    {
        std::shared_ptr<CLogMidiInputHandler> LogHandler(new CLogMidiInputHandler());
        MultiHandler.AddHandler(LogHandler);
    }

    CAlsaMidiInput MidiInput(MultiHandler);

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGILL, signal_handler);
    std::signal(SIGSEGV, signal_handler);
    std::signal(SIGFPE, signal_handler);
    std::signal(SIGABRT, signal_handler);

    // Run
    MidiInput.Open("Alsa2SerialMidiTool", "MidiIn");

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
