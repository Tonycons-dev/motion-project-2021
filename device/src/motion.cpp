#include "motion.hpp"
#include <Arduino.h>
#include <Wire.h>


inline float wrapf(float angle, float limit)
{
    while (angle >  limit) angle -= 2 * limit;
    while (angle < -limit) angle += 2 * limit;
    return angle;
}

MPU6050::MPU6050(TwoWire* twoWire)
{
    wire = twoWire;
    setGyroFilter(DEFAULT_GYRO_COEFF);
    reset();
}

void MPU6050::reset()
{
    setGyroOffsets(Vector3f());
    setAccOffsets (Vector3f());
    gyroValues   = Vector3f();
    accValues    = Vector3f();
    accAngles    = Vector2f();
    motionAngles = Vector3f();
    positions    = Vector3f();
    deadzoneMin  = Vector3f();
}

u8 MPU6050::connect(u16 gyroConfigNum, u16 accConfigNum)
{
    writeData(Registers::SMPLRT_DIV, 0x00);
    writeData(Registers::CONFIG, 0x00);

    setGyroConfig(gyroConfigNum);
    setAccConfig(accConfigNum);

    writeData(Registers::POWERLEVEL1, 0x00);

    update();
    preInterval = millis();
    return true;
}

u8 MPU6050::writeData(u8 r, u8 data)
{
    wire->beginTransmission(Registers::I2C_ADDRESS);
    wire->write(r);
    wire->write(data);

    u8 status = wire->endTransmission();
    return status;
}

u8 MPU6050::readData(u8 r)
{
    wire->beginTransmission(Registers::I2C_ADDRESS);
    wire->write(r);

    wire->endTransmission(true);
    wire->requestFrom(Registers::I2C_ADDRESS, 1);

    u8 data = wire->read();
    return data;
}

u8 MPU6050::setGyroConfig(int configNum)
{
    switch (configNum)
    { case 0x00: 
    {
        gyroToDegSec = 131.0f;
        return writeData(Registers::GYRO_CONFIG, 0x00);
    } case 0x01: 
    {
        gyroToDegSec = 65.5f;
        return writeData(Registers::GYRO_CONFIG, 0x08);
    } case 0x02: 
    {
        gyroToDegSec = 32.8f;
        return writeData(Registers::GYRO_CONFIG, 0x10);
    } case 0x03: 
    {
        gyroToDegSec = 16.4f;
        return writeData(Registers::GYRO_CONFIG, 0x18);
    }}
    return 1;
}

u8 MPU6050::setAccConfig(int configNum)
{
    switch (configNum)
    { case 0x00:
    {
        accToGValue = 16384.0f;
        return writeData(Registers::ACC_CONFIG, 0x00);
    } case 0x01:
    {
        accToGValue = 8192.0f;
        return writeData(Registers::ACC_CONFIG, 0x08);
    } case 0x02:
    {
        accToGValue = 4096.0f;
        return writeData(Registers::ACC_CONFIG, 0x10);
    } case 0x03:
    {
        accToGValue = 2048.0f;
        return writeData(Registers::ACC_CONFIG, 0x18);
    }}
    return 1;
}

void MPU6050::setGyroFilter(float gyroFilter)
{
    filterGyro =
    ((gyroFilter < 0.0f) || (gyroFilter > 1.0f)) ? 
        DEFAULT_GYRO_COEFF : gyroFilter;
}

void MPU6050::setAccFilter(float accFilter)
{
    setGyroFilter(1.0f - accFilter);
}

void MPU6050::calibrate(bool calcGyro, bool calcAcc)
{
    if (calcGyro) setGyroOffsets(Vector3<float>(0.0f, 0.0f, 0.0f));
    if (calcAcc ) setAccOffsets (Vector3<float>(0.0f, 0.0f, 0.0f));

    Vector3<float> acc;
    Vector3<float> gyro;

    for (word i = 0x0000; i < CALIB_OFFSET_NB_MES; i++)
    {
        pollData(); 
        acc.x  += accValues.x;
        acc.y  += accValues.y;
        acc.z  += accValues.z - 1.0f;
        gyro.x += gyroValues.x;
        gyro.y += gyroValues.y;
        gyro.z += gyroValues.z;
        delay(1);
    }
    if (calcAcc)
        accOffsets  = acc  / (float)CALIB_OFFSET_NB_MES;
    if (calcGyro)
        gyroOffsets = gyro / (float)CALIB_OFFSET_NB_MES;
}

void MPU6050::pollData()
{
    wire->beginTransmission(Registers::I2C_ADDRESS);
    wire->write(Registers::ACC_OUTPUT);
    wire->endTransmission(false);
    wire->requestFrom((int)(Registers::I2C_ADDRESS), 0x0E);

    int16_t rawData[7];
    for (u8 i = 0x00; i < 0x07; i++)
    {
        rawData[i]  = wire->read() << 8;
        rawData[i] |= wire->read();
    }

    accValues.x  = ((float)rawData[0]) / accToGValue - accOffsets.x;
    accValues.y  = ((float)rawData[1]) / accToGValue - accOffsets.y;

    accValues.z  = (!reverseMounting - reverseMounting) * 
        ((float)rawData[2]) / accToGValue - accOffsets.z;

    temperature  = (rawData[3] + TEMP_LSB_OFFSET) / TEMP_LSB_2_DEGREE;

    gyroValues.x = ((float)rawData[4]) / gyroToDegSec - gyroOffsets.x;
    gyroValues.y = ((float)rawData[5]) / gyroToDegSec - gyroOffsets.y;
    gyroValues.z = ((float)rawData[6]) / gyroToDegSec - gyroOffsets.z;
}

void MPU6050::update()
{
    pollData();
    const auto z0 = (accValues.z >= 0) - (accValues.z < 0);
    const auto z1 = powf(accValues.z, 2);

    accAngles.x =  atan2f(accValues.y, z0 * 
        sqrtf(z1 + powf(accValues.x, 2)) * 57.29578f);

    accAngles.y = -atan2f(accValues.x,
        sqrtf(z1 + powf(accValues.y, 2)) * 57.29578f);

    const auto  t = millis();
    float dt = (t - preInterval) * (float)(1e-3);
    preInterval = t;
    
    motionAngles.x  = wrapf(filterGyro * (
        accAngles.x + wrapf(motionAngles.x + 
        gyroValues.x * dt - accAngles.x, 180.0f)) + 
        (1.0f - filterGyro) * accAngles.x, 180.0f);

    motionAngles.y  = wrapf(filterGyro * (
        accAngles.y + wrapf(motionAngles.y + 
        z0 * gyroValues.x * dt - accAngles.y, 90.0f)) + 
        (1.0f - filterGyro) * accAngles.y, 90.0f);

    motionAngles.z += gyroValues.z * dt;

    Vector3<float> n = positions;
    n += gyroValues;

    if ((positions.x - n.x) < deadzoneMin.x || (positions.x - n.x) > deadzoneMax.x)
        positions.x  = n.x;

    if ((positions.y - n.y) < deadzoneMin.y || (positions.y - n.y) > deadzoneMax.y)
        positions.y  = n.y;

    if ((positions.z - n.z) < deadzoneMin.z || (positions.z - n.z) > deadzoneMax.z)
        positions.z  = n.z;
}