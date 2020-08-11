//
// Created by Jason Laqua on 8/11/20.
//

#include "DataFormatter.h"

String DataFormatter::toString(const EulerAngles &orientation, const EulerAngles &orientationDerivative,
                               sensors_event_t gyroData) {
    String entry = String();
    entry += "x: ";
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
