#include <cstring>
#include "LinuxSerialPort.h"
//linux specific stuff
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */


CLinuxSerialPort::CLinuxSerialPort()
    : m_FileDescriptor(-1)
{
    std::memset(&m_PrevProperties, 0, sizeof(m_PrevProperties));
}

CLinuxSerialPort::~CLinuxSerialPort()
{
    Close();
}

namespace
{

unsigned short GetBaudrate(int Baudrate)
{
    switch(Baudrate)
    {
        case 600:
            return B600;
        case 1200:
            return B1200;
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
        default:
            return B115200;
    }
}

}

bool CLinuxSerialPort::Open(const std::string &Name, int Baudrate, int /*Parity*/)
{
    int Flags = O_RDWR | O_NOCTTY | O_SYNC;
    m_FileDescriptor = open(Name.c_str(), Flags);
    if(0<=m_FileDescriptor)
    {
        // remember current properties, so we can restore upon close
        std::memset(&m_PrevProperties, 0, sizeof(m_PrevProperties));
        if(tcgetattr (m_FileDescriptor, &m_PrevProperties) != 0)
        {
            perror("error %d from tcgetattr");
            return false;
        }

        // setting properties of the serial port
        struct termios Termios;
        memset(&Termios, 0, sizeof(Termios));
        Termios.c_cflag = GetBaudrate(Baudrate) | CS8 | CLOCAL | CREAD;
        Termios.c_iflag = IGNPAR;
        Termios.c_oflag = 0;
        Termios.c_lflag = 0;    // set input mode (non-canonical, no echo,...)

        // parity is ignored => no parity
        Termios.c_cc[VTIME] = 1;//0.1 sec timeout
        Termios.c_cc[VMIN] = 0;// 0 => no blocking, 1 => block untill at least 1 is read

        if(tcflush(m_FileDescriptor, TCIFLUSH) <0)
        {
            perror("error %d from tcsetattr");
            return false;
        }

        if (tcsetattr (m_FileDescriptor, TCSANOW, &Termios) < 0)
        {
            perror("error %d from tcsetattr");
            return false;
        }
    }

    return IsOpen();
}

bool CLinuxSerialPort::IsOpen() const
{
    return (-1 != m_FileDescriptor);
}

void CLinuxSerialPort::Close()
{
    if(IsOpen())
    {
        if (tcsetattr(m_FileDescriptor, TCSANOW, &m_PrevProperties) != 0)
        {
            perror("error %d from tcsetattr");
        }
        close(m_FileDescriptor);
        m_FileDescriptor = -1;
    }
}

int CLinuxSerialPort::Read(BufferType &Buffer, int Number)
{
    BufferType ReadBuffer(Number, 0);
    int NumRead = read(m_FileDescriptor, ReadBuffer.data(), ReadBuffer.size());
    if(0<NumRead)
    {
        Buffer.insert(Buffer.end(), ReadBuffer.begin(), ReadBuffer.begin() + NumRead);
    }
    return NumRead;
}

int CLinuxSerialPort::Write(const CLinuxSerialPort::BufferType &Buffer)
{
    return write(m_FileDescriptor, Buffer.data(), Buffer.size());
}
