#include <Arduino.h>
#include "components/Motors.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int tickTime = 10; //basically the clock
int x = 1000; //the time to wait before starting
int y = 2000; //the time to move forward at the beginning

Motors motors;
IRSensor ir;
LineFollower lineFollower;

enum State {start, firstForward, stall, reverse, searchLeft, searchRight, forward};

State currentState = start;

void setup() {
    motors.init(9, 10);
    ir.init(2);
}

long startTime = -1;
long waitTime = 0;
boolean smartWait(long timeToWait) {
    if (startTime < 0) { //new smartWait task
        startTime = millis();
        waitTime = timeToWait;
    } else {
        if (millis() - startTime > timeToWait) {
            startTime = -1;
            return true;
        }
    }
    return false;
}

void stateStart() {
    if (smartWait(x)) {
        currentState = firstForward;
    }
}

void stateFirstForward() {
    motors.setBothMotors(100);
    if (smartWait(y)) {
        //TODO: add backwards condition
        if (lineFollower.seeLine()) {
            currentState = reverse;
        } else {
            currentState = searchLeft;
        }
    }
}

void stateStall() {

}

void stateReverse() {

}

void stateSearchLeft() {

}

void stateSearchRight() {

}

void stateForward() {

}

void loop() {
    ir.update();

    switch (currentState) {
        case start: stateStart(); break;
        case firstForward:stateFirstForward(); break;
        case stall: stateStall(); break;
        case reverse: stateReverse(); break;
        case searchLeft: stateSearchLeft(); break;
        case searchRight: stateSearchRight(); break;
        case forward: stateForward(); break;
    }

    delay(tickTime);
}