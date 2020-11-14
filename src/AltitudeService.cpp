//
// Created by Jason Laqua on 9/12/20.
//

#include "AltitudeService.h"

int AltitudeService::init() {
    return init(Adafruit_BMP280::MODE_NORMAL,
                Adafruit_BMP280::SAMPLING_X2,
                Adafruit_BMP280::SAMPLING_X16,
                Adafruit_BMP280::FILTER_X16,
                Adafruit_BMP280::STANDBY_MS_500);
}

int AltitudeService::init(Adafruit_BMP280::sensor_mode mode, Adafruit_BMP280::sensor_sampling tempSampling,
                          Adafruit_BMP280::sensor_sampling pressSampling, Adafruit_BMP280::sensor_filter filter,
                          Adafruit_BMP280::standby_duration duration) {
    int status = bmp.begin();
    if (status) {
        bmp.setSampling(mode, tempSampling, pressSampling, filter, duration);
    }
    return status;
}

int AltitudeService::calibrate() {
    groundLevelAltitude = bmp.readAltitude(SEA_LEVEL_PRESSURE);
    return 1;
}

float AltitudeService::altitude() {
    return bmp.readAltitude(SEA_LEVEL_PRESSURE) - groundLevelAltitude;
}

float AltitudeService::temperature() {
    return bmp.readTemperature();
}

float AltitudeService::pressure() {
    return bmp.readPressure();
}
