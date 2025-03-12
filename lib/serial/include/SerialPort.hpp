#ifndef _SERIAL_PORT_
#define _SERIAL_PORT_

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH   255

#include <iostream>

class SerialPort
{
private:
    bool connected;
#ifdef _WIN32
public:
    typedef struct _ComStat 
    {
        unsigned long fCtsHold  : 1;
        unsigned long fDsrHold  : 1;
        unsigned long fRlsdHold : 1;
        unsigned long fXoffHold : 1;
        unsigned long fXoffSent : 1;
        unsigned long fEof      : 1;
        unsigned long fTxim     : 1;
        unsigned long fReserved : 25;
        unsigned long cbInQue;
        unsigned long cbOutQue;
    } ComStat;
    ComStat status;
private:
    void* handler;
    unsigned long errors;
#else
public: int mDeviceHandle{};
#endif
public:
    enum PortID : int
    {
        USB_0, USB_1, USB_2,
        USB_3, USB_4, USB_5,
        USB_6, USB_7, USB_8
    };

    explicit SerialPort(PortID portID);
    ~SerialPort();

    int readSerialPort(const char *buffer, unsigned int buf_size);
    bool writeSerialPort(const char *buffer, unsigned int buf_size);
    bool isConnected();
    void closeSerial();
};
#endif