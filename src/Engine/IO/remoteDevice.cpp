/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -remoteDevice.cpp-
 *   Functionality for parsing microcontroller motion data.
 */

#include <Engine/IO/remoteDevice.hpp>
#include <Engine/IO/remoteConnection.hpp>

bool anim::RemoteDevice::initialize()
{
    mRemote = new RemoteConnection();
    mTimer  = std::clock();

    return this->isReady();
}

bool anim::RemoteDevice::isReady() const
{
    if (mRemote == nullptr)
        return false;
    
    if (!mRemote->isReady())
        return false;
    
    return true;
}

void anim::RemoteDevice::terminate()
{
    if (mRemote != nullptr)
        delete mRemote;
}

template<typename T>
void splitMessage(const std::string& str, char delimiter, T result)
{
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter))
        *result++ = token;
}

std::vector<std::string> splitMessage(const char* buffer, char delimiter)
{
    std::vector<std::string> elements;
    splitMessage(buffer, delimiter, std::back_inserter(elements));

    return elements;
}

void anim::RemoteDevice::update()
{   
    if (mRemote == nullptr)
        return;

    if ((std::clock() - mTimer) < io::DEVICE_UPDATE_DELAY)
        return;

    mTimer = std::clock();
    char* buffer(mRemote->readBufferTimeout(io::DEVICE_TIMEOUT_DELAY));

    mOldData = mNewData;
    
    if (!isMessageValid(buffer))
        return;

    s32 index = 0;
    for (std::string& token : splitMessage(buffer, ','))
    {
		if (index > 15)
			break;

		if (token.front() == io::DEVICE_MESSAGE_BEGIN)
			token[0] = ' ';

        else if (token.back() == io::DEVICE_MESSAGE_END)
            token.pop_back();

		mNewData[index++] = std::stof(token);
    }
}

bool anim::RemoteDevice::isMessageValid(char* buffer)
{
    if (buffer == nullptr)
        return false;
    
    std::string message(buffer);

    if (message.front() == io::DEVICE_MESSAGE_BEGIN 
     && message.back()  == io::DEVICE_MESSAGE_END)
        return true;

    return false;
}