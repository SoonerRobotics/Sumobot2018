#include <Arduino.h>
#include "components/Motors.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int tickTime = 1000; //time between ticks in microseconds
int x = 500; //the time to wait before starting
int y = 2000; //the time to move forward at the beginning
int z = 1500; //the time to move backwards when on a line

Motors motors;
IRSensor ir;
LineFollower frontLF;
LineFollower backLF;
//           0           1         2      3         4            5           6
enum State {start, firstForward, stall, reverse, searchLeft, searchRight, forward};

State currentState = start;

void setup() {
    motors.init(9, 10);
    ir.init(3);
    frontLF.init(1);
    Serial.begin(9600);
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

void stateStall() {
    motors.setBothMotors(0);
}

void stateSearchLeft() {
    motors.setMotorLeft(-40);
    motors.setMotorRight(40);

    if (ir.getDistance() < 30) {
        currentState = forward;
    }
}

void stateSearchRight() {

}

void stateForward() {
    motors.setBothMotors(75);

    if  (frontLF.seeLine()) {
        currentState = reverse;
    }
}

void stateReverse() {
    motors.setBothMotors(-75);

    if (smartWait(z)) {
        //currentState = searchLeft;
        currentState = searchLeft;
    }
}

void loop() {
    ir.update();

    Serial.println(ir.getDistance());

    switch (currentState) {
        case start: stateStart(); break;
        case stall: stateStall(); break;
        case reverse: stateReverse(); break;
        case searchLeft: stateSearchLeft(); break;
        case searchRight: stateSearchRight(); break;
        case forward: stateForward(); break;
    }
}
