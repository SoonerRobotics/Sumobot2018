#include <Arduino.h>
#include "components/Motors.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int tickTime = 500; //time between ticks in microseconds
int x = 500; //the time to wait before starting
int y = 2000; //the time to move forward at the beginning
int z = 1500; //the time to move backwards when on a line

Motors motors;
IRSensor ir;
LineFollower frontLF;
LineFollower backLF;

enum State {start, firstForward, stall, reverse, searchLeft, searchRight, forward};

State currentState = start;

void setup() {
    motors.init(9, 10);
    ir.init(2);
    frontLF.init(0);
}

long startTime = -1;
long waitTime = 0;
boolean smartWait(long timeToWait) {
    if (startTime < 0) { //new smartWait task
        startTime = millis();
        waitTime = timeToWait;
    } else {
        if ((long)millis() - startTime > timeToWait) {
            startTime = -1;
            return true;
        }
    }
    return false;
}


void stateStart() {
    if (smartWait(x)) {
        //currentState = firstForward;
        currentState = forward;
    }
}

void stateFirstForward() {
    motors.setBothMotors(50);
    if (smartWait(y)) {
        //TODO: add backwards condition
        if (frontLF.seeLine()) {
            currentState = reverse;
        } else {
            currentState = searchLeft;
        }
    }
}

void stateStall() {
    motors.setBothMotors(0);
    if (smartWait(1000)) {
        currentState = reverse;
    }
}

void stateReverse() {
    motors.setBothMotors(-100);
    if (smartWait(z)) {
        //currentState = searchLeft;
        currentState = forward;
    }
}

void stateSearchLeft() {

}

void stateSearchRight() {

}

void stateForward() {
    motors.setBothMotors(100);

    if  (frontLF.seeLine()) {
        currentState = stall;
    }
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

    delayMicroseconds(tickTime);
}