/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -remoteDevice.hpp-
 *   Functionality for parsing microcontroller motion data.
 */

#ifndef _ANIM_IO_REMOTE_MGR_
#define _ANIM_IO_REMOTE_MGR_

#include <Core/Types/BasicTypes.hpp>
#include <Core/Utils/Vector2.hpp>
#include <Core/Utils/Vector3.hpp>
#include "Engine/Constants/ioConstants.hpp"

namespace anim {

class RemoteConnection;
class RemoteDevice
{
public:
    bool initialize();
    bool isReady() const;

    void terminate();
    void update();

private:
    std::array<float, 17> mNewData{};
    std::array<float, 17> mOldData{};

    RemoteConnection* mRemote{};
    
    long mTimer = 0L;
    bool isMessageValid(char* buffer);

public:
    inline const std::array<float, 17>& getNewData() const {
        return mNewData;
    }

    inline const std::array<float, 17>& getOldData() const {
        return mOldData;
    }

    inline vec3f getPosition() const noexcept { 
        return vec3f(mNewData[0], mNewData[1], mNewData[2]); 
    }

    inline vec3f getVelocity() const noexcept {
        return vec3f(mNewData[3], mNewData[4], mNewData[5]); 
    }

    inline vec3f getAcceleration() const noexcept {
        return vec3f(mNewData[6], mNewData[7], mNewData[8]); 
    }

    inline vec3f getGyroscope() const noexcept {
        return vec3f(mNewData[9], mNewData[10], mNewData[11]);
    }

    inline vec3f getMotionAngles() const noexcept {
        return vec3f(mNewData[12], mNewData[13], mNewData[14]);
    }

    inline vec2f getAccelAngles() const noexcept {
        return vec2f(mNewData[15], mNewData[16]);
    }
};
}
#endif