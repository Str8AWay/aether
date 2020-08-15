//
// Created by Jason Laqua on 8/15/20.
//

#ifndef AETHER_ORIENTATIONSERVICE_H
#define AETHER_ORIENTATIONSERVICE_H


#include <Adafruit_BNO055.h>
#include "Quaternion.h"

class OrientationService {
private:
    Quaternion _rotationQuat;
    Quaternion _orientationDerivative;
    Quaternion _orientation;

    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
    sensors_event_t angVelocityData;
    sensors_event_t prev;
    double x_adjust;
    double y_adjust;
    double z_adjust;
    int readGyro();

public:
    int init(Adafruit_BNO055::adafruit_bno055_gyrorange_t range, Adafruit_BNO055::adafruit_bno055_gyrospeed_t bandwidth);
    void zero();
    void calibrate(int numOfReadings);
    int update();
    Quaternion orientation();
    Quaternion orientationDerivative();
    sensors_event_t rawGyro();
};


#endif //AETHER_ORIENTATIONSERVICE_H
