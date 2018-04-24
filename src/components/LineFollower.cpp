#include "LineFollower.h"

#include <Arduino.h>

void LineFollower::init(int _pin) {
    pin = _pin;
    setUp = true;

    pinMode(pin, INPUT);
}

bool LineFollower::seeLine() {
    
    return analogRead(pin) <= 200;
}