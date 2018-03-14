#include "LineFollower.h"

#include <Arduino.h>

void LineFollower::init(int _pin) {
    pin = _pin;
    setUp = true;
}

bool LineFollower::seeLine() {

    if (analogRead(pin) >= 950) {
        return false;
    }
    return true;
}