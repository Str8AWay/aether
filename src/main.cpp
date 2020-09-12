#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Logger.h>
#include <IMUService.h>
#include "DataFormatter.h"
#include "RGB.h"

#define LED_RED 2
#define LED_GREEN 1
#define LED_BLUE 0

Logger logger = Logger(INFO);
IMUService imuService;
RGB rgb = RGB(LED_RED, LED_GREEN, LED_BLUE);

enum RocketState {
    STARTUP,
    CALIBRATION,
    READY_FOR_LAUNCH,
    POWERED_ASCENT,
    COAST,
    APOGEE,
    FREE_FALL,
    DROGUE_DESCENT,
    MAIN_CHUTE_DESCENT,
    LANDED,
    DATA_TRANSFER,
    FLIGHT_COMPLETE
} rocketState;

void setup() {
    rocketState = STARTUP;
    rgb.init();
    rgb.setColor(255, 0, 0);
    if (!imuService.init(Adafruit_BNO055::GYRO_RANGE_250, Adafruit_BNO055::GYRO_BANDWIDTH_230)) {
        logger.error("Error initializing orientation service");
        while (true);
    }
    delay(2000);
    rocketState = CALIBRATION;
}

void loop() {
    boolean orientationUpdate = imuService.updateOrientation();
    boolean accelerationUpdate = imuService.updateAccelerometer();
    if (orientationUpdate) {
        logger.info(DataFormatter::toString(rocketState, imuService.orientation().toEuler(), imuService.orientationDerivative().toEuler(), imuService.rawGyro()));
    }
    switch (rocketState) {
        case CALIBRATION:
            rgb.setColor(255, 255, 0);
            imuService.calibrateGyro(1000);
            imuService.zero();
            rocketState = READY_FOR_LAUNCH;
            break;
        case READY_FOR_LAUNCH:
            rgb.setColor(0, 255, 0);
            if (accelerationUpdate && imuService.acceleration().y > -7) {
                rocketState = POWERED_ASCENT;
            }
            break;
        case POWERED_ASCENT:
            break;
        case COAST:
            break;
        case APOGEE:
            break;
        case FREE_FALL:
            break;
        case DROGUE_DESCENT:
            break;
        case MAIN_CHUTE_DESCENT:
            break;
        case LANDED:
            break;
        case DATA_TRANSFER:
            break;
        case FLIGHT_COMPLETE:
            break;
    }
}