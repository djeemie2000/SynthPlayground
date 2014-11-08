
/** @file simple_client.c
   *
   * @brief This is very simple client that demonstrates the basic
   * features of JACK as they would be used by many applications.
   */

#include <unistd.h>//std::sleep
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <cstring>
//linux specific stuff
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

class CLinuxSerialPort
{
public:
    typedef std::vector<std::uint8_t> BufferType;

    CLinuxSerialPort();

    bool Open(const std::string& Name, int Baudrate, int Parity);
    bool IsOpen() const;
    void Close();

    int Read(BufferType& Buffer, int Number); //!< read number and append to buffer. return number actually read
    int Write(const BufferType& Buffer); //!< write buffer. returns number actually written

private:
    int m_FileDescriptor;
    termios m_PrevProperties;
};





CLinuxSerialPort::CLinuxSerialPort()
    : m_FileDescriptor(-1)
{
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

bool CLinuxSerialPort::Open(const std::string &Name, int Baudrate, int Parity)
{
    int Flags = O_RDWR | O_NOCTTY | O_SYNC;
    m_FileDescriptor = open(Name.c_str(), Flags);
    if(0<=m_FileDescriptor)
    {
        // remember current properties, so we can restore upon close
        memset(&m_PrevProperties, 0, sizeof(m_PrevProperties));
        if (tcgetattr (m_FileDescriptor, &m_PrevProperties) != 0)
        {
            perror("error %d from tcgetattr");
            return false;
        }


        // setting properties of the serial port
//        struct termios tty;
//        memset(&tty, 0, sizeof(tty));
//        if (tcgetattr (m_FileDescriptor, &tty) != 0)
//        {
//            perror("error %d from tcgetattr");
//            return false;
//        }

        struct termios Termios;
        memset(&Termios, 0, sizeof(Termios));
        Termios.c_cflag = GetBaudrate(Baudrate) | CS8 | CLOCAL | CREAD;
        Termios.c_iflag = IGNPAR;
        Termios.c_oflag = 0;
        Termios.c_lflag = 0;    // set input mode (non-canonical, no echo,...)

        // parity is ignored => no parity
        Termios.c_cc[VTIME] = 1;//0.1 sec timeout
        Termios.c_cc[VMIN] = 0;// 0 => no blocking, 1 => block untill at least 1 is read


//        cfsetospeed(&tty, Baudrate);
//        cfsetispeed(&tty, Baudrate);

//        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
//        tty.c_iflag |= (IGNBRK | IGNPAR);

//        tty.c_oflag = 0;                // no remapping, no delays
//        tty.c_cc[VMIN]  = 0;            // 0 => read doesn't block, 1 => read blocks untill at least 1 byte is recieved
//        tty.c_cc[VTIME] = 5;            // 5 * 0.1 = 0.5 seconds read timeout

  //      tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
  //      tty.c_iflag &= ~(ISTRIP);
  //      tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
//        tty.c_cflag &= ~(PARENB | PARODD | HUPCL);      // shut off parity
//        tty.c_cflag |= Parity;
//        tty.c_cflag &= ~CSTOPB;
//        tty.c_cflag &= ~CRTSCTS;
//        tty.c_lflag = 0;
//        // ???? flush will give strange results for the first few reads
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


void PrintBuffer(const CLinuxSerialPort::BufferType& Buffer)
{
    for(auto& Char : Buffer)
    {
        std::cout << "0x" << std::hex << int(Char) << " ";
    }
    std::cout << std::endl;
}

int main (int /*argc*/, const char **/*argv[]*/)
{
    CLinuxSerialPort SerialPort;
    std::cout << "Opening serial port" << std::endl;
    if(!SerialPort.Open("/dev/ttyACM0", 9600, 0))
    {
        std::cout << "failed!" << std::endl;
    }

    std::cout << "Reading from serial port" << std::endl;
    CLinuxSerialPort::BufferType Buffer;
    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        SerialPort.Read(Buffer, 3);
        std::cout << Repeat << " : ";
        PrintBuffer(Buffer);
    }

    std::cout << "Closing serial port" << std::endl;
    SerialPort.Close();

    return 0;
}
