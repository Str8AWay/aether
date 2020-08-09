#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Logger.h>
#include "Quaternion.h"

Logger logger = Logger(INFO);

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

sensors_event_t angVelocityData;
sensors_event_t prev;

void printData(double dt, sensors_event_t gyroData, Quaternion rotation, Quaternion orientation, EulerAngles euler) {
    logger.info("dt (s): ");
    logger.info(dt);
    logger.info(", x (deg/s): ");
    logger.info(gyroData.gyro.x);
    logger.info(", y (deg/s): ");
    logger.info(gyroData.gyro.y);
    logger.info(", z (deg/s): ");
    logger.info(gyroData.gyro.z);
//  logger.info(", rotW: ");
//  logger.info(rotation.w);
//  logger.info(", rotX: ");
//  logger.info(rotation.x);
//  logger.info(", rotY: ");
//  logger.info(rotation.y);
//  logger.info(", rotZ: ");
//  logger.info(rotation.z);
    logger.info(", oriW: ");
    logger.info(orientation.w);
    logger.info(", oriX: ");
    logger.info(orientation.x);
    logger.info(", oriY: ");
    logger.info(orientation.y);
    logger.info(", oriZ: ");
    logger.info(orientation.z);
    logger.info(", pitch: ");
    logger.info(euler.pitch * 180.0/PI);
    logger.info(", yaw: ");
    logger.info(euler.yaw * 180.0/PI);
    logger.info(", roll: ");
    logger.info(euler.roll * 180.0/PI);
    logger.info("\n");
}

void setup() {
    if (!bno.begin(Adafruit_BNO055::OPERATION_MODE_ACCGYRO))
    {
        logger.error("No BNO055 found");
        while (1);
    }

//    bno.setGyroConfig(Adafruit_BNO055::GYRO_RANGE_2000, Adafruit_BNO055::GYRO_BANDWIDTH_523);

    prev.timestamp = millis();
}

Quaternion rotationQuat;
Quaternion orientation = {1.0, 0.0, 0.0, 0.0};
void loop() {
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    if (angVelocityData.gyro.x != prev.gyro.x || angVelocityData.gyro.y != prev.gyro.y || angVelocityData.gyro.z != prev.gyro.z) {
        double dt = (angVelocityData.timestamp - prev.timestamp) / 1000.0;
        EulerAngles angles{};
        angles.yaw = angVelocityData.gyro.x*PI/180.0*dt;
        angles.pitch = angVelocityData.gyro.y*PI/180.0*dt;
        angles.roll = angVelocityData.gyro.z*PI/180.0*dt;
        rotationQuat = Quaternion(angles);
        rotationQuat.normalize();
        orientation = rotationQuat * orientation;
        orientation.normalize();
        EulerAngles euler = orientation.toEuler();

        printData(dt, angVelocityData, rotationQuat, orientation, euler);

        prev.timestamp = angVelocityData.timestamp;
        prev.gyro.x = angVelocityData.gyro.x;
        prev.gyro.y = angVelocityData.gyro.y;
        prev.gyro.z = angVelocityData.gyro.z;
    }
}