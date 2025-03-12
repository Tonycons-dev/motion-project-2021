#ifndef _MPU_6050_H_
#define _MPU_6050_H_

#include "constants.hpp"


#define CALIB_OFFSET_NB_MES   500
#define TEMP_LSB_2_DEGREE     340.0
#define TEMP_LSB_OFFSET       12412.0
#define DEFAULT_GYRO_COEFF    0.98


class TwoWire;
class MPU6050
{
    TwoWire* wire;
public:
    Vector3f gyroOffsets;
    Vector3f accOffsets;
    Vector3f gyroValues;
    Vector3f accValues;
    Vector3f motionAngles;
    Vector3f positions;
    Vector3f deadzoneMin;
    Vector3f deadzoneMax;
    Vector2f accAngles;

    long preInterval;
    float gyroToDegSec;
    float accToGValue;
    float filterGyro;
    float temperature;

    bool reverseMounting;

    enum Registers : u8
    {
        I2C_ADDRESS = 0x68,
        SMPLRT_DIV  = 0x19,
        CONFIG      = 0x1A,
        GYRO_CONFIG = 0x1B,
        ACC_CONFIG  = 0x1C,
        POWERLEVEL1 = 0x6B,
        GYRO_OUTPUT = 0x43,
        ACC_OUTPUT  = 0x3B
    };

    //Prepare the MPU6050 with a pointer to the Wire instance.
    MPU6050(TwoWire* w);

    //Initialize the MPU6050 to communicate data.
    //This needs to be called before any other member function,
    //and should only be called once in the scope of this class.
    //Returns 0 if the MPU6050 could not be detected.
    u8 connect(u16 gyroConfigNum = 1, u16 accConfigNum = 0);

    //Sets all the data retrieved from the MPU6050 to zero.
    //Does not restart the sensor, it will continue to run.
    void reset();

    //Retrieves all the necessary data from the MPU6050.
    void pollData();

    //Calls the pollData function and calculates the angle, 
    //gyro, and position values as well.
    //IMPORTANT: floating point values returned by the sensor
    //will lose precision over time. Update should be called
    //only as much as necessary.
    void update();

    //Writes 8 bits to the specified register of the MPU6050.
    u8 writeData(u8 r, u8 data);

    //Returns 8 bits from the specified register of the MPU6050/
    u8 readData(u8 r);

    //Automatically calibrates the MPU6050. Optional arguments
    //specify which components should be calibrated.
    void calibrate(bool calcGyro = true, bool calcAcc = true);

    u8 setGyroConfig(int configNum);
    u8 setAccConfig (int configNum);

    void setGyroFilter (float gyroFilter);
    void setAccFilter  (float accFilter);

    //Offset the value of the gyroscope. Should be used if the gyroscope values
    //while the device is still are not close to zero.

    inline void setGyroOffsets(Vector3f offset) { gyroOffsets = offset; }

    //Offset the value of the accelerometer. Should be used if the accelerometer 
    //values while the device is still are not close to zero.

    inline void setAccOffsets (Vector3f offset) { accOffsets  = offset; }

    //Sets how high and low the gyro values have to be for the position to change.
    inline void setDeadzones(Vector3f _min, Vector3f _max)
    {
        deadzoneMax = _max;
        deadzoneMin = _min;
    }
};
#endif