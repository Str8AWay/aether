#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Logger.h>
#include "Quaternion.h"
#include "DataFormatter.h"

Logger logger = Logger(INFO);

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

sensors_event_t angVelocityData;
sensors_event_t prev;

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
        rotationQuat.w = 0;
        rotationQuat.x = radians(angVelocityData.gyro.x);
        rotationQuat.y = radians(angVelocityData.gyro.y);
        rotationQuat.z = radians(angVelocityData.gyro.z);
        Quaternion orientationDerivative = orientation * 0.5 * rotationQuat;
        orientation = orientation + orientationDerivative * dt;
        orientation.normalize();
        EulerAngles euler = orientation.toEuler();

        logger.info(DataFormatter::toString(euler, orientationDerivative.toEuler(), angVelocityData));

        prev.timestamp = angVelocityData.timestamp;
        prev.gyro.x = angVelocityData.gyro.x;
        prev.gyro.y = angVelocityData.gyro.y;
        prev.gyro.z = angVelocityData.gyro.z;
    }
}