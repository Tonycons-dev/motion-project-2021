#include <SerialPort.hpp>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>
#include <asm/ioctls.h>

void configureTermios(SerialPort* port);

const char* PORT_NAME_USB0 = "/dev/ttyUSB0",
          * PORT_NAME_USB1 = "/dev/ttyUSB1",
          * PORT_NAME_USB2 = "/dev/ttyUSB2",
          * PORT_NAME_USB3 = "/dev/ttyUSB3",
          * PORT_NAME_USB4 = "/dev/ttyUSB4",
          * PORT_NAME_USB5 = "/dev/ttyUSB5",
          * PORT_NAME_USB6 = "/dev/ttyUSB6",
          * PORT_NAME_USB7 = "/dev/ttyUSB7",
          * PORT_NAME_USB8 = "/dev/ttyUSB8";

SerialPort::SerialPort(PortID portID)
{
    const char* portName{};

    switch (portID) {
        case PortID::USB_0: { portName = PORT_NAME_USB0; break; }
        case PortID::USB_1: { portName = PORT_NAME_USB1; break; }
        case PortID::USB_2: { portName = PORT_NAME_USB2; break; }
        case PortID::USB_3: { portName = PORT_NAME_USB3; break; }
        case PortID::USB_4: { portName = PORT_NAME_USB4; break; }
        case PortID::USB_5: { portName = PORT_NAME_USB5; break; }
        case PortID::USB_6: { portName = PORT_NAME_USB6; break; }
        case PortID::USB_7: { portName = PORT_NAME_USB7; break; }
        case PortID::USB_8: { portName = PORT_NAME_USB8; break; }
        default:            { portName = PORT_NAME_USB0; break; }
    }

    this->connected = false;

    if (portName == nullptr)
        std::cerr << "[SerialPort] Invalid port name.\n";

    mDeviceHandle = open("/dev/ttyUSB0", O_RDWR);

    if (mDeviceHandle == -1)
        std::cerr << "[SerialPort] Could not open device " << portName << "\n";

    configureTermios(this);
    this->connected = true;
}


SerialPort::~SerialPort()
{
    if (isConnected())
        closeSerial();
}

int SerialPort::readSerialPort(const char *buffer, unsigned int buf_size)
{
    if (mDeviceHandle <= 0) {
        std::cerr << "[SerialPort] Read was called but device was not open.\n";
        return 0;
    }

    if (buffer == nullptr)
        return 0;

    auto readSize = read(mDeviceHandle, (void*)buffer, buf_size);

    if (readSize < 0)
        throw std::system_error(EFAULT, std::system_category());

    return static_cast<int>(readSize);
}

bool SerialPort::writeSerialPort(const char *buffer, unsigned int buf_size)
{
    if (mDeviceHandle <= 0) {
        std::cerr << "[SerialPort] Write was called but device was not open.\n";
        return false;
    }

    if (buffer == nullptr)
        return false;

    auto writeResult = write(mDeviceHandle, buffer, buf_size);

    if (writeResult == -1)
        throw std::system_error(EFAULT, std::system_category());

    return true;
}

bool SerialPort::isConnected()
{
    connected = mDeviceHandle <= 0;
    return connected;
}

void SerialPort::closeSerial()
{
    if (mDeviceHandle != -1)
    {
        auto closeStatus = close(mDeviceHandle);

        if (closeStatus != 0)
            std::cerr << "[SerialPort] Close failed.\n";

        mDeviceHandle = -1;
    }
    connected = false;
}

void configureTermios(SerialPort* port)
{
    struct termios2 term{};
    ioctl(port->mDeviceHandle, TCGETS2, &term);

    term.c_cflag &= ~PARENB;
    term.c_cflag &= ~CSTOPB;
    term.c_cflag &= ~CSIZE;
    term.c_cflag |= CS8;
    term.c_cflag &= ~CRTSCTS;
    term.c_cflag |= CREAD | CLOCAL;
    term.c_cflag &= ~CBAUD;
    term.c_cflag |= CBAUDEX;

    term.c_ispeed = 9600;
    term.c_ospeed = 9600;

    term.c_oflag = 0;
    term.c_oflag &= ~OPOST;

    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 0;

    term.c_iflag &= ~(IXON | IXOFF | IXANY);
    term.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHOE;
    term.c_lflag &= ~ECHONL;
    term.c_lflag &= ~ISIG;

    ioctl(port->mDeviceHandle, TCSETS2, &term);
}