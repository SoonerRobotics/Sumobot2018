#include "Magnets.h"

#include <Arduino.h>

void Magnets::init(int _pin) {
    pin = _pin;
    setUp = true;

    pinMode(pin, OUTPUT);
}

void Magnets::setState(bool on) {
    digitalWrite(pin, on);
    isOn = on;
}