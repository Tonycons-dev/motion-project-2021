#ifndef _ANIM_RT_TRANSFER_
#define _ANIM_RT_TRANSFER_

#include "constants.hpp"

class MPU6050;
struct MotionDataPacket
{
    Vector3f positions   {};
    Vector3f velocity    {};
    Vector3f acceleration{};
    Vector3f gyroValues  {};
    Vector3f motionAngles{};    
    Vector2f accAngles   {};
};
void beginTransmission();

void updatePackets(MotionDataPacket& newPacket, MotionDataPacket& oldPacket, MPU6050& mpu);
void transmitPacket(MotionDataPacket& packet);

#endif