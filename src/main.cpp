#include <Arduino.h>
#include "components/Motors.h"
#include "components/IRSensor.h"
#include "components/LineFollower.h"

int tickTime = 1000; //time between ticks in microseconds
int x = 500; //the time to wait before starting
int y = 2000; //the time to move forward at the beginning
int z = 500; //the time to move backwards when on a line

Motors motors;
IRSensor leftSensor;
IRSensor rightSensor;
LineFollower fline0;
LineFollower fline1;

enum State {start, center, stall, search, reverse, chase, forward};

State currentState = start;
bool yellow = true;
bool goLeft = false;

void setup() {
    motors.init(9, 10);
    leftSensor.init(2);
    rightSensor.init(3);
    fline0.init(0);
    fline1.init(1);
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
    motors.setBothMotors(0);
    if (smartWait(x)) {
        //currentState = firstForward;
        currentState = center;
    }
}

void stateStall() {
    motors.setBothMotors(0);
}

void stateSearch(bool red) {
    if(yellow){
        motors.setMotorLeft(25);
        motors.setMotorRight(-25);
        yellow = false;

    }

    if ((rightSensor.getDistance() < 30) && (leftSensor.getDistance() < 30)) { // detect in front
        currentState = chase;
    }
   else  if ((rightSensor.getDistance() < 30) && !(leftSensor.getDistance() < 30)) { // detect right sensor
        motors.setMotorRight(30);
        motors.setMotorLeft(-30);
        Serial.println("right");
        goLeft = false;
    }
    else if (!(rightSensor.getDistance() < 30) && (leftSensor.getDistance() < 30)) { // detect left sensor
        motors.setMotorRight(-30);
        motors.setMotorLeft(30);
        Serial.println("left");
        goLeft = true;
    }
    else if (!(rightSensor.getDistance() < 30) && !(leftSensor.getDistance() < 30)){
        if(goLeft){
            motors.setMotorLeft(40);
            motors.setMotorRight(-40);
        }
        else if(!goLeft){
            motors.setMotorLeft(-40);
            motors.setMotorRight(40);
        }
       
    }
}
void stateChase(){
    motors.setBothMotors(75);
    if  (fline0.seeLine() || fline1.seeLine()) {
        currentState = reverse;
        return;
    }
   else if (!(rightSensor.getDistance() < 30) || !(leftSensor.getDistance() < 30)){
        currentState = search;
    }

}

void stateCenter(){
    motors.setBothMotors(75);
if (smartWait(500)) {
      motors.setBothMotors(0); 
         if  (fline0.seeLine() || fline1.seeLine()) {
        currentState = reverse;
        return;
        }
        if ((rightSensor.getDistance() < 30) && (leftSensor.getDistance() < 30)) { // detect in front
            currentState = chase;
            Serial.println("alles gut");
        }
        else {
        yellow = true;
        currentState = search;
    
      }
    }



}

void stateForward() {
    motors.setBothMotors(50);
}

void stateReverse() {
    motors.setBothMotors(-75);
    if (smartWait(z)) {
        //currentState = searchLeft;
       motors.setBothMotors(0);
       yellow = true;
        currentState = search;
    }
}

void loop() {
    leftSensor.update();
    rightSensor.update();
    Serial.println(true);

    switch (currentState) {
        case start: stateStart(); break;
        case center: stateCenter(); break;
        case stall: stateStall(); break;
        case reverse: stateReverse(); break;
        case search: stateSearch(yellow); break;
        case chase: stateChase(); break;
        case forward: stateForward(); break;
    }
}