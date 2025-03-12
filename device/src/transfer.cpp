#include "transfer.hpp"
#include "motion.hpp"
#include <Arduino.h>

static auto* serial = &Serial;


void beginTransmission()
{
    pinMode(TRANSMIT_PIN, OUTPUT);
    pinMode(RECEIVE_PIN, INPUT);

    serial->begin(DEFAULT_BAUD);
    delay(255);
}

void updatePackets(MotionDataPacket& packet, MotionDataPacket& oldPacket, MPU6050& mpu)
{
    packet.positions    = mpu.positions;
    packet.velocity     = packet.positions - oldPacket.positions;
    packet.acceleration = mpu.accValues;
    packet.gyroValues   = mpu.gyroValues;
    packet.motionAngles = mpu.motionAngles;
    packet.accAngles    = mpu.accAngles;
}

void transmitPacket(MotionDataPacket& packet)
{
    serial->write(MESSAGE_BEGIN);
    //float* packetData = reinterpret_cast<float*>(&packet);
    
    float packetData[17] = 
    {
        packet.positions.x,    packet.positions.y,    packet.positions.z,
        packet.velocity.x,     packet.velocity.y,     packet.velocity.z,
        packet.acceleration.x, packet.acceleration.y, packet.acceleration.z,
        packet.gyroValues.x,   packet.gyroValues.y,   packet.gyroValues.z,
        packet.motionAngles.x, packet.motionAngles.y, packet.motionAngles.z,
        packet.accAngles.x,    packet.accAngles.y
    };

    for (int i = 0; i < 17; i++)
    {
        char data[40]{};
        dtostrf(packetData[i], 4, 2, data);

        serial->write(data);
        serial->write(',');
    }
    serial->write(MESSAGE_OVER);
}