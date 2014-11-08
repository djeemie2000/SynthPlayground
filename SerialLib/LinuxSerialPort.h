#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <termios.h> /* POSIX terminal control definitions */
#include "SerialPortI.h"

class CLinuxSerialPort : public ISerialPort
{
public:
    CLinuxSerialPort();
    ~CLinuxSerialPort();

    bool Open(const std::string& Name, int Baudrate, int Parity) override;
    bool IsOpen() const override;
    void Close() override;

    int Read(BufferType& Buffer, int Number) override; //!< read number and append to buffer. return number actually read
    int Write(const BufferType& Buffer) override; //!< write buffer. returns number actually written

private:
    int m_FileDescriptor;
    termios m_PrevProperties;
};
