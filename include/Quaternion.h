//
// Created by Jason Laqua on 8/8/20.
//

#ifndef AETHER_QUATERNION_H
#define AETHER_QUATERNION_H


#include "EulerAngles.h"

class Quaternion {
public:
    double w;
    double x;
    double y;
    double z;

    Quaternion();
    Quaternion(double w, double x, double y, double z);
    explicit Quaternion(const EulerAngles& angles);
    Quaternion multiply(Quaternion quat) const;
    Quaternion operator*(const Quaternion& quat) const;
    Quaternion operator*(double scalar) const;
    Quaternion operator+(const Quaternion& quat) const;
    void normalize();
    EulerAngles toEuler() const;
};

#endif //AETHER_QUATERNION_H
