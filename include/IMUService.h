//
// Created by Jason Laqua on 8/15/20.
//

#ifndef AETHER_IMUSERVICE_H
#define AETHER_IMUSERVICE_H


#include <Adafruit_BNO055.h>
#include "Quaternion.h"
#include "Vector.h"

class IMUService {
private:
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

    // Rotation
    Quaternion _rotationQuat;
    Quaternion _orientationDerivative;
    Quaternion _orientation;

    sensors_event_t angVelocityData;
    sensors_event_t prevAngData;
    double x_gryo_adjust;
    double y_gryo_adjust;
    double z_gyro_adjust;
    int readGyro();

    // Position
    Vector _acceleration;

    sensors_event_t accelData;
    sensors_event_t prevAccelData;
    int readAccel();

public:
    int init(Adafruit_BNO055::adafruit_bno055_gyrorange_t range, Adafruit_BNO055::adafruit_bno055_gyrospeed_t bandwidth);
    void zero();
    void calibrateGyro(int numOfReadings);
    int updateOrientation();
    Quaternion orientation();
    Quaternion orientationDerivative();
    sensors_event_t rawGyro();

    int updateAccelerometer();
    Vector acceleration();
    sensors_event_t rawAccel();
};


#endif //AETHER_IMUSERVICE_H
