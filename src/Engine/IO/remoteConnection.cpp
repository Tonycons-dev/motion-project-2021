/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -remoteConnection.cpp-
 *   Functionality for handling communication with serial ports.
 */

#include <Engine/IO/remoteConnection.hpp>
#include "Engine/System/Runtime.hpp"
#include <iostream>
#include <vector>
#include <memory>
//#include <BluetoothException.h>
#include <SerialPort.hpp>

namespace anim {

const char* RemoteConnection::ComPorts::COM6 = "\\\\.\\COM6";
const char* RemoteConnection::ComPorts::COM2 = "\\\\.\\COM2";
const char* RemoteConnection::ComPorts::COM3 = "\\\\.\\COM3";
const char* RemoteConnection::ComPorts::COM4 = "\\\\.\\COM4";

}

anim::RemoteConnection::RemoteConnection(bool checkBluetooth)
{   
    ready = false;
    if (!trySerialPortConnection())
    {
        LOG_MESSAGE("Remote not connected.");
        return;          
    }
    LOG_MESSAGE("Remote connected.");
    ready = true;    
}

anim::RemoteConnection::~RemoteConnection()
{
    delete mSerialPort;
}

bool anim::RemoteConnection::trySerialPortConnection()
{
    LOG_MESSAGE("Scanning for serial ports.\n");

    if (checkSerialComPort(int(SerialPort::PortID::USB_6)))
        return true;

    if (Runtime::isDevWorkstation1())
        if (checkSerialComPort(int(SerialPort::PortID::USB_3)))
            return true;
    
    if (checkSerialComPort(int(SerialPort::PortID::USB_2)))
        return true;

    if (checkSerialComPort(int(SerialPort::PortID::USB_4)))
        return true;

    LOG_MESSAGE("No available serial ports.\n");
    return false;
}

bool anim::RemoteConnection::checkSerialComPort(int portID)
{
    mSerialPort = new SerialPort(SerialPort::PortID(portID));

    if (mSerialPort == nullptr)
        return false;

    std::cout << "[ANIM] Checking port " << portID << " ";

    if (mSerialPort->isConnected())
    {
        std::cout << "Connected YES\n";
        portOpen = true;
        return true;
    }
    delete mSerialPort;

    std::cout << "Connected NO\n";
    return false;
}

char* anim::RemoteConnection::readBuffer()
{
    if (!mSerialPort->isConnected())
        return nullptr;

    if (!mSerialPort->readSerialPort(mBuffer, BUFFER_SIZE))
        return nullptr;

    return mBuffer;
}

char* anim::RemoteConnection::readBufferTimeout(long ms)
{
    if (!mSerialPort->isConnected())
        return nullptr;
    
    std::clock_t timeout = std::clock() + ms;

    while (true)
    {
        if (std::clock() > timeout)
		{
            std::cout << "Serial read Timeout.\n";
            break;
        }
			
		char* buffer = this->readBuffer();
		if (buffer)
            return buffer;
    }
    return nullptr;
}

bool anim::RemoteConnection::writeBuffer(char data[BUFFER_SIZE])
{
    if (!mSerialPort->isConnected())
        return false;
    
    if (!mSerialPort->writeSerialPort(data, BUFFER_SIZE))
        return false;

    return true;
}

//bool anim::RemoteConnection::tryBluetoothConnection()
//{
//    mDevice = DeviceINQ::Create();
//
//    if (mDevice == nullptr)
//    {
//        LOG_FAILURE("Failed to allocate memory for Bluetooth.");
//        return false;
//    }
//
//    std::vector<device> devices;
//    try
//    {
//        LOG_MESSAGE("Scanning for bluetooth devices.");
//        devices = mDevice->Inquire();
//
//    } catch (const BluetoothException& e)
//    {
//        LOG_FAILURE(e.what());
//        return false;
//    }
//
//    LOG_MESSAGE("Found"<< devices.size() << "devices.");
//    for (const auto& dev : devices)
//    {
//        LOG_MESSAGE(dev.name << " " << dev.address);
//        if (dev.name == "DSD TECH")
//        {
//            LOG_MESSAGE("Found remote device.");
//            try
//            {
//                return createBluetoothSocket(dev);
//            }
//            catch (const BluetoothException& e)
//            {
//                LOG_FAILURE(e.what());
//                return false;
//            }
//        }
//    }
//    LOG_FAILURE("Could not find remote device.");
//    return false;
//}

//bool anim::RemoteConnection::createBluetoothSocket(const device& dev)
//{
//    s32 channelID{};
//    #ifdef _WIN32
//        channelID = 1;
//    #else
//        channelID = DeviceINQ::SdpSearch(dev.address);
//    #endif
//
//    if (channelID <= 0)
//		throw BluetoothException("ChannelID should be a positive int value");
//
//    mBinding = BTSerialPortBinding::Create(dev.address, channelID);
//
//    if (!mBinding)
//        throw BluetoothException("Could not allocate memory for BluetoothBinding");
//
//    mBinding->Connect();
//    LOG_MESSAGE("Connected successfully.");
//
//    if (mBinding->IsDataAvailable())
//	{
//        LOG_MESSAGE("Buffer data available.");
//
//		char buf[0xff];
//		mBinding->Read(buf, 0xff);
//
//        LOG_MESSAGE("Buffer data: " << buf << "\n");
//        return true;
//    }
//	else
//        LOG_MESSAGE("No buffer data available.");
//
//	mBinding->Close();
//    return false;
//}