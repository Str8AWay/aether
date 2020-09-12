//
// Created by Jason Laqua on 8/11/20.
//

#include "DataFormatter.h"

String DataFormatter::toString(int rocketState, const EulerAngles &orientation, const EulerAngles &orientationDerivative,
                               sensors_event_t gyroData) {
    String entry = String();
    entry += "[";
    entry += rocketState;
    entry += "] ";
    entry += millis();
    entry += " - x: ";
    entry += degrees(orientation.pitch);
    entry += ",\ty: ";
    entry += degrees(orientation.yaw);
    entry += ",\tz: ";
    entry += degrees(orientation.roll);
    entry += ",\td/dx: ";
    entry += degrees(orientationDerivative.pitch);
    entry += ",\td/dy: ";
    entry += degrees(orientationDerivative.yaw);
    entry += ",\td/dz: ";
    entry += degrees(orientationDerivative.roll);
    entry += ",\tgX: ";
    entry += gyroData.gyro.x;
    entry += ",\tgY: ";
    entry += gyroData.gyro.y;
    entry += ",\tgZ: ";
    entry += gyroData.gyro.z;
    return entry;
}

String DataFormatter::toString(const Vector &acceleration) {
    String entry = String();
    entry += millis();
    entry += " - x (m/s^2): ";
    entry += acceleration.x;
    entry += ",\ty (m/s^2): ";
    entry += acceleration.y;
    entry += ",\tz (m/s^2): ";
    entry += acceleration.z;
    return entry;
}