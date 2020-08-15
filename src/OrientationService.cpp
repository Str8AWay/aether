//
// Created by Jason Laqua on 8/15/20.
//

#include "OrientationService.h"

int OrientationService::init(Adafruit_BNO055::adafruit_bno055_gyrorange_t range,
                             Adafruit_BNO055::adafruit_bno055_gyrospeed_t bandwidth) {
    int status = bno.begin(Adafruit_BNO055::OPERATION_MODE_ACCGYRO);
    if (status) {
        bno.setGyroConfig(Adafruit_BNO055::GYRO_RANGE_250, Adafruit_BNO055::GYRO_BANDWIDTH_230);
        prev.timestamp = millis();
    }
    return status;
}

void OrientationService::zero() {
    _orientation.w = 1;
    _orientation.x = 0;
    _orientation.y = 0;
    _orientation.z = 0;
    _orientationDerivative.w = 0;
    _orientationDerivative.x = 0;
    _orientationDerivative.y = 0;
    _orientationDerivative.z = 0;
}

void OrientationService::calibrate(int numOfReadings) {
    x_adjust = 0;
    y_adjust = 0;
    z_adjust = 0;
    double x = 0, y = 0, z = 0;
    int reading = 0;
    while (reading < numOfReadings)
    {
        if (readGyro()) {
            x += radians(angVelocityData.gyro.x);
            y += radians(angVelocityData.gyro.y);
            z += radians(angVelocityData.gyro.z);
            reading++;
        }
    }
    x_adjust = x / numOfReadings;
    y_adjust = y / numOfReadings;
    z_adjust = z / numOfReadings;
}

int OrientationService::update() {
    if (readGyro()) {
        double dt = (angVelocityData.timestamp - prev.timestamp) / 1000.0;
        _orientationDerivative = _orientation * 0.5 * _rotationQuat;
        _orientation = _orientation + _orientationDerivative * dt;
        _orientation.normalize();

        prev.timestamp = angVelocityData.timestamp;
        prev.gyro.x = angVelocityData.gyro.x;
        prev.gyro.y = angVelocityData.gyro.y;
        prev.gyro.z = angVelocityData.gyro.z;
        return 1;
    }
    return 0;
}

Quaternion OrientationService::orientation() {
    return _orientation;
}

Quaternion OrientationService::orientationDerivative() {
    return _orientationDerivative;
}

sensors_event_t OrientationService::rawGyro() {
    return angVelocityData;
}

int OrientationService::readGyro() {
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    if (angVelocityData.gyro.x != prev.gyro.x || angVelocityData.gyro.y != prev.gyro.y || angVelocityData.gyro.z != prev.gyro.z) {
        _rotationQuat.w = 0;
        _rotationQuat.x = radians(angVelocityData.gyro.x) - x_adjust;
        _rotationQuat.y = radians(angVelocityData.gyro.y) - y_adjust;
        _rotationQuat.z = radians(angVelocityData.gyro.z) - z_adjust;
        return 1;
    }
    return 0;
}