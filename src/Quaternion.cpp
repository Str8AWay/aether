//
// Created by Jason Laqua on 8/8/20.
//

#include <cmath>
#include "Quaternion.h"

Quaternion::Quaternion() {
    w = 1;
    x = 0;
    y = 0;
    z = 0;
}

Quaternion::Quaternion(double w, double x, double y, double z) {
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion(const EulerAngles &angles) {
    double cy = cos(angles.yaw * 0.5);
    double sy = sin(angles.yaw * 0.5);
    double cp = cos(angles.pitch * 0.5);
    double sp = sin(angles.pitch * 0.5);
    double cr = cos(angles.roll * 0.5);
    double sr = sin(angles.roll * 0.5);

    w = cr*cp*cy + sr*sp*sy;
    x = sr*cp*cy - cr*sp*sy;
    y = cr*sp*cy + sr*cp*sy;
    z = cr*cp*sy - sr*sp*cy;
}

Quaternion Quaternion::multiply(Quaternion quat) const {
    Quaternion result{};
    result.w = w*quat.w - x*quat.x - y*quat.y - z*quat.z;
    result.x = w*quat.x + quat.w*x + y*quat.z - z*quat.y;
    result.y = w*quat.y + quat.w*y + z*quat.x - x*quat.z;
    result.z = w*quat.z + quat.w*z + x*quat.y - y*quat.x;
    return result;
}

Quaternion Quaternion::operator*(const Quaternion &quat) const {
    return multiply(quat);
}

Quaternion Quaternion::operator*(double scalar) const {
    Quaternion result{};
    result.w = w * scalar;
    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;
    return result;
}

Quaternion Quaternion::operator+(const Quaternion &quat) const {
    Quaternion result{};
    result.w = w + quat.w;
    result.x = x + quat.x;
    result.y = y + quat.y;
    result.z = z + quat.z;
    return result;
}

void Quaternion::normalize() {
    double norm = sqrt(w*w + x*x + y*y + z*z);
    w = w/norm;
    x = x/norm;
    y = y/norm;
    z = z/norm;
}

EulerAngles Quaternion::toEuler() const {
    EulerAngles angles{};
    
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (w * x + y * z);
    double cosr_cosp = 1 - 2 * (x * x + y * y);
    angles.roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (w * y - z * x);
    if (std::abs(sinp) >= 1)
        angles.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    angles.yaw = atan2(siny_cosp, cosy_cosp);
    return angles;
}
