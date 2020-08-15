#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Logger.h>
#include <OrientationService.h>
#include "DataFormatter.h"

Logger logger = Logger(INFO);

OrientationService orientationService;

void setup() {
    if (!orientationService.init(Adafruit_BNO055::GYRO_RANGE_250, Adafruit_BNO055::GYRO_BANDWIDTH_230)) {
        logger.error("Error initializing orientation service");
        while (true);
    }
    orientationService.calibrate(1000);
    orientationService.zero();
}

void loop() {
    if (orientationService.update()) {
        logger.info(DataFormatter::toString(orientationService.orientation().toEuler(), orientationService.orientationDerivative().toEuler(), orientationService.rawGyro()));
    }
}