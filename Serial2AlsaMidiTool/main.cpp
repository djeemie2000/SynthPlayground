#include <iostream>
#include <string>
//#include <thread>
#include "LinuxSerialPort.h"
#include "AlsaMidiOutput.h"
#include "RawMidiParser.h"

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


int main(int argc, const char* argv[])
{
    About();

    std::string Port = ParsePort(argc, argv);
    int Baudrate = ParseBaudrate(argc, argv);

    CAlsaMidiOutput MidiOutput;
    std::cout << "Opening midi output" << std::endl;
    MidiOutput.Open("Serial2AlsaMidiTool", "MidiOut");

    CLinuxSerialPort SerialPort;
    CLogMidiInputHandler MidiHandlerTemp;
    CRawMidiParser MidiParser(MidiHandlerTemp);

    std::cout << "Opening serial port " << Port << " (" << Baudrate << ")" << std::endl;
    if(!SerialPort.Open(Port, Baudrate, 0))
    {
        std::cout << "failed!" << std::endl;
    }
    else
    {

        for(int Repeat = 0; Repeat<100; ++Repeat)
        {
            // read from serial
            CLinuxSerialPort::BufferType Buffer;
            SerialPort.Read(Buffer, 3);

            PrintBuffer(Buffer);//debug

            // parse serial and send parsed midi data to alsa
            MidiParser.Parse(Buffer);
        }

        // wait untill keypressed
    //    char bs = std::getchar();

    }


    std::cout << "Closing serial port "  << Port << " (" << Baudrate << ")" << std::endl;
    SerialPort.Close();

    std::cout << "Closing midi output" << std::endl;
    MidiOutput.Close();

    About();

    return 0;
}
