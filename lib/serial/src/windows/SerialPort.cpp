#ifdef _WIN32

#include <SerialPort.hpp>
#include <Windows.h>

static COMSTAT toComstat(const SerialPort::ComStat& comstat)
{
    return *reinterpret_cast<COMSTAT*>(&comstat);
}

static SerialPort::ComStat fromComstat(const COMSTAT& comstat)
{
    return *reinterpret_cast<SerialPort::ComStat*>(&comstat);
}

const char * PORT_NAME_USB0 = "\\\\.\\COM0",
           * PORT_NAME_USB1 = "\\\\.\\COM1",
           * PORT_NAME_USB2 = "\\\\.\\COM2",
           * PORT_NAME_USB3 = "\\\\.\\COM3",
           * PORT_NAME_USB4 = "\\\\.\\COM4",
           * PORT_NAME_USB5 = "\\\\.\\COM5",
           * PORT_NAME_USB6 = "\\\\.\\COM6",
           * PORT_NAME_USB7 = "\\\\.\\COM7",
           * PORT_NAME_USB8 = "\\\\.\\COM8";

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
    this->handler = CreateFileA
    (
        static_cast<LPCSTR>(portName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (this->handler == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            std::cerr << "ERROR: Handle was not attached.Reason : " << portName << " not available\n";
        else
            std::cerr << "ERROR!!!\n";
    }
    else
    {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(this->handler, &dcbSerialParameters))
            std::cerr << "Failed to get current serial parameters\n";
        else
        {
            dcbSerialParameters.BaudRate    = CBR_9600;
            dcbSerialParameters.ByteSize    = 8;
            dcbSerialParameters.StopBits    = ONESTOPBIT;
            dcbSerialParameters.Parity      = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
                std::cout << "ALERT: could not set serial port parameters\n";
            else
            {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->connected)
    {
        this->connected = false;
        CloseHandle(this->handler);
    }
}

int SerialPort::readSerialPort(const char *buffer, unsigned int buf_size)
{
    COMSTAT com = toComstat(this->status);
    DWORD bytesRead{};

    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &com);
    this->status = fromComstat(com);

    if (this->status.cbInQue > 0)
    {
        if (this->status.cbInQue > buf_size)
            toRead = buf_size;
        else
            toRead = this->status.cbInQue;
    }

    memset((void*) buffer, 0, buf_size);

    if (ReadFile(this->handler, (void*) buffer, toRead, &bytesRead, NULL))
        return bytesRead;

    return 0;
}

bool SerialPort::writeSerialPort(const char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void*)buffer, buf_size, &bytesSend, 0))
    {
        COMSTAT com = toComstat(this->status);
        ClearCommError(this->handler, &this->errors, &com);

        this->status = fromComstat(com);
        return false;  
    }

    return true;
}

bool SerialPort::isConnected()
{
    COMSTAT com = toComstat(this->status);

    if (!ClearCommError(this->handler, &this->errors, &com))
        this->connected = false;

    this->status = fromComstat(com);
    return this->connected;
}

void SerialPort::closeSerial()
{
    CloseHandle(this->handler);
}

#endif