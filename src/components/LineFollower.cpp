#include "LineFollower.h"

#include <Arduino.h>

void LineFollower::init(int _pin) {
    pin = _pin;
    setUp = true;

    pinMode(pin, INPUT);
}

bool LineFollower::seeLine() {

    if (analogRead(pin) >= 800) {
        return false;
    }
    return true;
}