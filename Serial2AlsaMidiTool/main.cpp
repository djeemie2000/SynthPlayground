#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "LinuxSerialPort.h"
#include "AlsaMidiOutput.h"
#include "RawMidiParser.h"
#include "ContinuousThreadRunner.h"

#include "LogMidiInputHandler.h"


using namespace std;

void About()
{
    std::cout << "-------------------" << std::endl;
    std::cout << "Serial2AlsaMidiTool" << std::endl;
    std::cout << "-------------------" << std::endl;
}

void PrintBuffer(const CLinuxSerialPort::BufferType& Buffer)
{
    if(!Buffer.empty())
    {
        for(auto& Char : Buffer)
        {
            std::cout << "0x" << std::hex << int(Char) << " ";
        }
        std::cout << std::endl;
    }
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

class CSerial2AlsaMidi
{
public:
    CSerial2AlsaMidi();

    bool Open(const std::string& SerialPort, int SerialBaudrate);
    void Close();

    void OnTick();
private:
    CAlsaMidiOutput m_MidiOutput;
    CLinuxSerialPort m_SerialPort;
    CLogMidiInputHandler m_MidiHandlerVerbose;
    CRawMidiParser m_MidiParser;
};

CSerial2AlsaMidi::CSerial2AlsaMidi()
 : m_MidiOutput()
 , m_SerialPort()
// , m_MidiHandlerVerbose()
 , m_MidiParser(m_MidiOutput)
{
}

bool CSerial2AlsaMidi::Open(const string &SerialPort, int SerialBaudrate)
{
    bool IsOpen = false;
    std::cout << "Opening midi output" << std::endl;
    if(m_MidiOutput.Open("Serial2AlsaMidiTool", "MidiOut"))
    {
        std::cout << "Opening serial port " << SerialPort << " (" << SerialBaudrate << ")" << std::endl;
        if(m_SerialPort.Open(SerialPort, SerialBaudrate, 0))
        {
            IsOpen = true;
        }
        else
        {
            std::cout << "failed!" << std::endl;
        }
    }
    else
    {
        std::cout << "failed!" << std::endl;
    }
    return IsOpen;
}

void CSerial2AlsaMidi::Close()
{
    std::cout << "Closing serial port" << std::endl;
    m_SerialPort.Close();

    std::cout << "Closing midi output" << std::endl;
    m_MidiOutput.Close();
}

void CSerial2AlsaMidi::OnTick()
{
    // read from serial
    CLinuxSerialPort::BufferType Buffer;
    m_SerialPort.Read(Buffer, 3);

    // PrintBuffer(Buffer);//verbose

    // parse serial and send parsed midi data to alsa
    m_MidiParser.Parse(Buffer);
}

int main(int argc, const char* argv[])
{
    About();
    std::cout << "Press any key to abort!" << std::endl;

    std::string Port = ParsePort(argc, argv);
    int Baudrate = ParseBaudrate(argc, argv);

    CSerial2AlsaMidi Controller;
    CContinuousThreadRunner<CSerial2AlsaMidi> ThreadRunner(Controller);

    if(Controller.Open(Port, Baudrate))
    {
        ThreadRunner.Start();
    }

    // wait untill keypressed
    char bs = std::getchar();

    ThreadRunner.Stop();
    Controller.Close();

    About();

    return 0;
}
