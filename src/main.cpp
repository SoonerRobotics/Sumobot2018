#include <Arduino.h>
#include "components/Motors.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

#define startDelay 500 //Milliseconds to wait before starting
#define reverseTime 500 //Milliseconds to move backwards when robo detects a line
#define centerTime 500 //Milliseconds to run to the center at the start of the match

#define detectRange 30 //Distance to detect robots at with IR

Motors motors;
IRSensor leftSensor;
IRSensor rightSensor;
LineFollower fline0; //front line follower 0
LineFollower fline1; //front line follower 1

enum State {start, center, stall, search, reverse, chase, forward};
State currentState = start;

void setup() {
    motors.init(9, 10);

    leftSensor.init(2);
    rightSensor.init(3);

    fline0.init(0);
    fline1.init(1);

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
}

bool primeSearch = true;
void stateSearch() {

    if(primeSearch){
        motors.setMotorLeft(25);
        motors.setMotorRight(-25);
        primeSearch = false;
    }

    bool detectL = rightSensor.getDistance() < detectRange;
    bool detectR = leftSensor.getDistance() < detectRange;

    if (detectR && detectL) { // detect in front
        primeSearch = true;
        currentState = chase;
    }
    else if (detectR && !detectL) { // detect right sensor
        motors.setMotorRight(30);
        motors.setMotorLeft(-30);
    }
    else if (!detectR && detectL) { // detect left sensor
        motors.setMotorRight(-30);
        motors.setMotorLeft(30);
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
    if (smartWait(centerTime)) {
        motors.setBothMotors(0);
        if  (fline0.seeLine() || fline1.seeLine()) {
            currentState = reverse;
            return;
        }
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