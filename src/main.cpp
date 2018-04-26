#include <Arduino.h>
#include "components/Motors.h"
#include "components/Magnets.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int startDelay = 500; // Milliseconds to wait before starting
int reverseTime = 500; // Milliseconds to move backwards when robo detects a line
int centerTime = 500; // Milliseconds to run to the center at the start of the match

int detectRange = 30; // Distance to detect robots at with IR

Motors motors;

IRSensor leftSensor;
IRSensor rightSensor;

LineFollower fline0; // front line follower 0
LineFollower fline1; // front line follower 1

Magnets magnets;

// The possible states the robot can be in
enum State {start, center, stall, search, reverse, chase};

// The current state of the robot
State currentState = start;

// Inital Setup
void setup() {
    motors.init(9, 10);

    leftSensor.init(2);
    rightSensor.init(3);

    fline0.init(0);
    fline1.init(1);

    magnets.init(2);

    Serial.begin(9600); //TODO: delete for tournament final
}

// This is the SmartWait (tm) function that will wait a specific time until returning true.
long smartWait_startTime = -1;
boolean smartWait(long timeToWait) {
    if (smartWait_startTime < 0) { // A new smartWait task was created
        smartWait_startTime = millis();
    } else {
        if ((long)millis() - smartWait_startTime > timeToWait) { // Have we waited long enough?
            smartWait_startTime = -1;
            return true;
        }  
    }
    return false;
}

// The inital state of the robot
void stateStart() {
    motors.setBothMotors(0);
    if (smartWait(startDelay)) {
        currentState = center;
    }
}

// When all hope is lost, turn on the magnets and stop the motors
void stateStall() {
    motors.setBothMotors(0);
    magnets.setState(true);
}

// Searching for robots, and if one is found switch to the chase state
bool lastLookingRight = true;
void stateSearch() {

    if (fline0.seeLine() || fline1.seeLine()) { // Uh oh, we see white! Back up!
        currentState = stall;
        return;
    }

    bool detectL = leftSensor.getDistance() < detectRange;
    bool detectR = rightSensor.getDistance() < detectRange;

    if (detectR && detectL) {       // detect with both sensors, so chase
        currentState = chase;
    }
    else if (detectR && !detectL) { // detect right IR sensor, turn right
        lastLookingRight = true;
        motors.setMotorRight(-30);
        motors.setMotorLeft(30);
    }
    else if (!detectR && detectL) { // detect left IR sensor, turn left
        lastLookingRight = false;
        motors.setMotorRight(30);
        motors.setMotorLeft(-30);
    } else {                        // don't see anything, so spin
        if (lastLookingRight) {
            motors.setMotorRight(-30);
            motors.setMotorLeft(30);
        } else {
            motors.setMotorRight(30);
            motors.setMotorLeft(-30);
        }
    }
}

// We spotted a robot! Chase after it, and if we lose sight then go back to search
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

// After the match starts, go towards the center then go into search
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

// When the front line follower see white, go backwards for a bit then continue searching
void stateReverse() {
    motors.setBothMotors(-75);
    if (smartWait(reverseTime)) {
        //currentState = searchLeft;
        motors.setBothMotors(0);
        currentState = search;
    }
}

// Each "tick" of the program
void loop() {
    
    // Update line sensor information
    leftSensor.update();
    rightSensor.update();

    // Update motor interpolation
    motors.update();

    // Call the appropriate function for the appropriate state
    switch (currentState) {
        case start: stateStart(); break;
        case center: stateCenter(); break;
        case stall: stateStall(); break;
        case reverse: stateReverse(); break;
        case search: stateSearch(); break;
        case chase: stateChase(); break;
    }
}