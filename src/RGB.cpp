//
// Created by Jason Laqua on 8/15/20.
//

#include "RGB.h"

RGB::RGB(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
    _redPin = redPin;
    _greenPin = greenPin;
    _bluePin = bluePin;
}

void RGB::init() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void RGB::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    analogWrite(_redPin, 255 - red);
    analogWrite(_greenPin, 255 - green);
    analogWrite(_bluePin, 255 - blue);
}
