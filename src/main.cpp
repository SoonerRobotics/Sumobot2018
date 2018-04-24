#include <Arduino.h>
#include "components/Motors.h"
#include "components/Magnets.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int startDelay = 500; //Milliseconds to wait before starting
int reverseTime = 500; //Milliseconds to move backwards when robo detects a line
int centerTime = 500; //Milliseconds to run to the center at the start of the match

int detectRange = 30; //Distance to detect robots at with IR

Motors motors;
IRSensor leftSensor;
IRSensor rightSensor;
LineFollower fline0; //front line follower 0
LineFollower fline1; //front line follower 1

Magnets magnets;

enum State {start, center, stall, search, reverse, chase, forward};
State currentState = start;

void setup() {
    motors.init(9, 10);

    leftSensor.init(2);
    rightSensor.init(3);

    fline0.init(0);
    fline1.init(1);

    magnets.init(2);

    Serial.begin(9600); //TODO: delete for tournament final
}

//don't touch these variables pls
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
    motors.setBothMotors(0);
    if (smartWait(startDelay)) {
        currentState = center;
    }
}

void stateStall() {
    motors.setBothMotors(0);
    magnets.setState(true);
}

bool lastLookingRight = true;
void stateSearch() {

    if (fline0.seeLine() || fline1.seeLine()) {
        currentState = stall;
        return;
    }

    bool detectL = leftSensor.getDistance() < detectRange;
    bool detectR = rightSensor.getDistance() < detectRange;

    if (detectR && detectL) { // detect in front
        currentState = chase;
    }
    else if (detectR && !detectL) { // detect right sensor
        lastLookingRight = true;
        motors.setMotorRight(-30);
        motors.setMotorLeft(30);
    }
    else if (!detectR && detectL) { // detect left sensor
        lastLookingRight = false;
        motors.setMotorRight(30);
        motors.setMotorLeft(-30);
    } else {
        if (lastLookingRight) {
            motors.setMotorRight(-30);
            motors.setMotorLeft(30);
        } else {
            motors.setMotorRight(30);
            motors.setMotorLeft(-30);
        }
    }
}
void stateChase(){
    motors.setBothMotors(75);
    if  (fline0.seeLine() || fline1.seeLine()) {
        currentState = reverse;
        return;
    }
    else if (!(rightSensor.getDistance() < detectRange) || !(leftSensor.getDistance() < detectRange)){
        currentState = search;
    }
}

void stateCenter(){
    motors.setBothMotors(75);
    if  (fline0.seeLine() || fline1.seeLine()) {
        currentState = reverse;
        return;
    }
    if (smartWait(centerTime)) {
        motors.setBothMotors(0);
        if ((rightSensor.getDistance() < detectRange) && (leftSensor.getDistance() < detectRange)) { // detect in front
            currentState = chase;
        }
        else {
            currentState = search;
        }
    }
}

void stateForward() {
    motors.setBothMotors(50);
}

void stateReverse() {
    motors.setBothMotors(-75);
    if (smartWait(reverseTime)) {
        //currentState = searchLeft;
        motors.setBothMotors(0);
        currentState = search;
    }
}

void loop() {
    leftSensor.update();
    rightSensor.update();

    motors.update();

    switch (currentState) {
        case start: stateStart(); break;
        case center: stateCenter(); break;
        case stall: stateStall(); break;
        case reverse: stateReverse(); break;
        case search: stateSearch(); break;
        case chase: stateChase(); break;
        case forward: stateForward(); break;
    }
}