//
// Created by Jason Laqua on 8/15/20.
//

#include "IMUService.h"

int IMUService::init(Adafruit_BNO055::adafruit_bno055_gyrorange_t range,
                     Adafruit_BNO055::adafruit_bno055_gyrospeed_t bandwidth) {
    int status = bno.begin(Adafruit_BNO055::OPERATION_MODE_ACCGYRO);
    if (status) {
        bno.setGyroConfig(Adafruit_BNO055::GYRO_RANGE_250, Adafruit_BNO055::GYRO_BANDWIDTH_230);
        prevAngData.timestamp = millis();
    }
    return status;
}

void IMUService::zero() {
    _orientation.w = 1;
    _orientation.x = 0;
    _orientation.y = 0;
    _orientation.z = 0;
    _orientationDerivative.w = 0;
    _orientationDerivative.x = 0;
    _orientationDerivative.y = 0;
    _orientationDerivative.z = 0;
    prevAngData.timestamp = millis();
}

void IMUService::calibrateGyro(int numOfReadings) {
    x_gryo_adjust = 0;
    y_gryo_adjust = 0;
    z_gyro_adjust = 0;
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
    x_gryo_adjust = x / numOfReadings;
    y_gryo_adjust = y / numOfReadings;
    z_gyro_adjust = z / numOfReadings;
}

int IMUService::updateOrientation() {
    if (readGyro()) {
        double dt = (angVelocityData.timestamp - prevAngData.timestamp) / 1000.0;
        _orientationDerivative = _orientation * 0.5 * _rotationQuat;
        _orientation = _orientation + _orientationDerivative * dt;
        _orientation.normalize();

        prevAngData.timestamp = angVelocityData.timestamp;
        prevAngData.gyro.x = angVelocityData.gyro.x;
        prevAngData.gyro.y = angVelocityData.gyro.y;
        prevAngData.gyro.z = angVelocityData.gyro.z;
        return 1;
    }
    return 0;
}

Quaternion IMUService::orientation() {
    return _orientation;
}

Quaternion IMUService::orientationDerivative() {
    return _orientationDerivative;
}

sensors_event_t IMUService::rawGyro() {
    return angVelocityData;
}

int IMUService::readGyro() {
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    if (angVelocityData.gyro.x != prevAngData.gyro.x || angVelocityData.gyro.y != prevAngData.gyro.y || angVelocityData.gyro.z != prevAngData.gyro.z) {
        _rotationQuat.w = 0;
        _rotationQuat.x = radians(angVelocityData.gyro.x) - x_gryo_adjust;
        _rotationQuat.y = radians(angVelocityData.gyro.y) - y_gryo_adjust;
        _rotationQuat.z = radians(angVelocityData.gyro.z) - z_gyro_adjust;
        return 1;
    }
    return 0;
}

int IMUService::updateAccelerometer() {
    if (readAccel()) {
        _acceleration.x = accelData.acceleration.x;
        _acceleration.y = accelData.acceleration.y;
        _acceleration.z = accelData.acceleration.z;
        return 1;
    }
    return 0;
}

sensors_event_t IMUService::rawAccel() {
    return accelData;
}

int IMUService::readAccel() {
    bno.getEvent(&accelData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    if (accelData.acceleration.x != prevAccelData.acceleration.x || accelData.acceleration.y != prevAccelData.acceleration.y || accelData.acceleration.z != prevAccelData.acceleration.z) {
        return 1;
    }
    return 0;
}

Vector IMUService::acceleration() {
    return _acceleration;
}
