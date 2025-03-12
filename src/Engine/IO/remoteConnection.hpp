/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -remoteConnection.hpp-
 *   Functionality for handling communication with serial ports.
 */

#ifndef _ANIM_IO_REMOTE_CONNECTION_
#define _ANIM_IO_REMOTE_CONNECTION_

#include <Core/Types/BasicTypes.hpp>
//#include <DeviceINQ.h>
//#include <BTSerialPortBinding.h>

class SerialPort;
namespace anim {

class RemoteConnection
{
public:
    static constexpr int BUFFER_SIZE = 0xff;
private:
    char mBuffer[BUFFER_SIZE]{0};

    //BTSerialPortBinding* mBinding{};
    //DeviceINQ* mDevice{};
    SerialPort* mSerialPort{};

    bool ready{};
    bool portOpen{};

    //bool tryBluetoothConnection();
    bool trySerialPortConnection();

    //bool createBluetoothSocket(const device& dev);
    bool checkSerialComPort(int portID);
public:
    struct ComPorts
    {
        static const char* COM6;
        static const char* COM2;
        static const char* COM3;
        static const char* COM4;
    };

    explicit RemoteConnection(bool checkBluetooth);
    RemoteConnection() : RemoteConnection(false){}

    ~RemoteConnection();

    char* readBufferTimeout(long ms);
    char* readBuffer();
    bool writeBuffer(char data[BUFFER_SIZE]);

    inline bool isReady() const noexcept { return ready; }
};
}
#endif