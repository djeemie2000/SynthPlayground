#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <termios.h> /* POSIX terminal control definitions */

class ISerialPort
{
public:
    typedef std::vector<std::uint8_t> BufferType;

    virtual ~ISerialPort(){}

    virtual bool Open(const std::string& Name, int Baudrate, int Parity) =0;
    virtual bool IsOpen() const =0;
    virtual void Close() =0;

    virtual int Read(BufferType& Buffer, int Number) =0; //!< read number and append to buffer. return number actually read
    virtual int Write(const BufferType& Buffer) =0; //!< write buffer. returns number actually written
};
