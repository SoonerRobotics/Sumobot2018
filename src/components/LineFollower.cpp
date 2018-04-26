#include "LineFollower.h"
#include <Arduino.h>

void LineFollower::init(int _pin) {
    pin = _pin;
    setUp = true;

    pinMode(pin, INPUT);
}

void LineFollower::init(int _pin, int _sensitivity) {
    pin = _pin;
    sensitivity = _sensitivity;
    setUp = true;

    pinMode(pin, INPUT);
}

bool LineFollower::seeLine() {
    return analogRead(pin) <= sensitivity;
}