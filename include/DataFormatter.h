//
// Created by Jason Laqua on 8/11/20.
//

#ifndef AETHER_DATAFORMATTER_H
#define AETHER_DATAFORMATTER_H

#include <Adafruit_Sensor.h>
#include "Arduino.h"
#include "EulerAngles.h"
#include "Vector.h"

class DataFormatter {
public:
    static String toString(int rocketState, const EulerAngles& orientation, const EulerAngles& orientationDerivative, sensors_event_t gyroData);
    static String toString(const Vector& acceleration);
};


#endif //AETHER_DATAFORMATTER_H
