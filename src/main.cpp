#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Logger.h>
#include <OrientationService.h>
#include "DataFormatter.h"
#include "RGB.h"

#define LED_RED 2
#define LED_GREEN 1
#define LED_BLUE 0

Logger logger = Logger(INFO);
OrientationService orientationService;
RGB rgb = RGB(LED_RED, LED_GREEN, LED_BLUE);

void setup() {
    rgb.init();
    rgb.setColor(255, 0, 0);
    if (!orientationService.init(Adafruit_BNO055::GYRO_RANGE_250, Adafruit_BNO055::GYRO_BANDWIDTH_230)) {
        logger.error("Error initializing orientation service");
        while (true);
    }
    rgb.setColor(255, 255, 0);
    orientationService.calibrate(1000);
    orientationService.zero();
    rgb.setColor(0, 255, 0);
}

void loop() {
    if (orientationService.update()) {
        logger.info(DataFormatter::toString(orientationService.orientation().toEuler(), orientationService.orientationDerivative().toEuler(), orientationService.rawGyro()));
    }
}