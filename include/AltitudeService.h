//
// Created by Jason Laqua on 9/12/20.
//

#ifndef AETHER_ALTITUDESERVICE_H
#define AETHER_ALTITUDESERVICE_H

static const float SEA_LEVEL_PRESSURE = 1013.25;

#include <Adafruit_BMP280.h>

class AltitudeService {
private:
    Adafruit_BMP280 bmp = Adafruit_BMP280();
    float groundLevelAltitude;

public:
    int init();
    int init(Adafruit_BMP280::sensor_mode mode, Adafruit_BMP280::sensor_sampling tempSampling,
                  Adafruit_BMP280::sensor_sampling pressSampling, Adafruit_BMP280::sensor_filter filter, Adafruit_BMP280::standby_duration duration);
    int calibrate();
    float altitude();
    float temperature();
    float pressure();
};


#endif //AETHER_ALTITUDESERVICE_H
