#include "motion.hpp"
#include "transfer.hpp"
#include <Wire.h>

static MPU6050 mpu(&Wire2);
static MotionDataPacket oldPacket{};
static MotionDataPacket newPacket{};

static u32 timer = 0;


void reset()
{
    #define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C)
    SCB_AIRCR = 0x05FA0004;
}

void setup()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(255);
    digitalWrite(LED_BUILTIN, LOW);
    delay(255);

    Wire2.begin();

    if (!mpu.connect())
    {
        digitalWrite(LED_BUILTIN, HIGH);
        while (true)
        {
            if (digitalRead(BUTTON_START))
                reset();
        }
    }

    mpu.calibrate();
    mpu.setDeadzones(minDeadzones, maxDeadzones);

    beginTransmission();

    updatePackets(oldPacket, oldPacket, mpu);
    transmitPacket(newPacket);
}

void loop()
{
    if (digitalRead(BUTTON_START))
        reset();

    if (millis() - timer > UPDATE_SPEED)
    {
        timer = millis();
        mpu.update();
        
        updatePackets(newPacket, oldPacket, mpu);
        transmitPacket(newPacket);

        oldPacket = newPacket;
    }
}