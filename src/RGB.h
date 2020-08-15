//
// Created by Jason Laqua on 8/15/20.
//

#ifndef AETHER_RGB_H
#define AETHER_RGB_H

#include <Arduino.h>

class RGB {
private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
public:
    RGB(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    void init();
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
};


#endif //AETHER_RGB_H
