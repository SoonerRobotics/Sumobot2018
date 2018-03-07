#include "LineFollower.h"

void LineFollower::init(int _pin) {
    pin = _pin;
    setUp = true;
}

bool LineFollower::seeLine() {
    return true; //just trigger false positive to stop in case of no trigger
    if (analogRead(pin) >= 950) {
        return false;
    }
    return true;
}