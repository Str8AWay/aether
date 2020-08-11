//
// Created by Jason Laqua on 8/11/20.
//

#ifndef AETHER_DATAFORMATTER_H
#define AETHER_DATAFORMATTER_H

#include <Adafruit_Sensor.h>
#include "Arduino.h"
#include "EulerAngles.h"

class DataFormatter {
public:
    static String toString(const EulerAngles& orientation, const EulerAngles& orientationDerivative, sensors_event_t gyroData);
};


#endif //AETHER_DATAFORMATTER_H
