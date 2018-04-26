#include "motors.h"

#include <Arduino.h>

void Motors::init(int leftMotor, int rightMotor) {

  if (setUp) {
    return;
  }

  setUp = true;


  //Create 2 servos that send a PWM signal from 1000-2000 Hz to the left and right motor pins
  servoLeft.attach(leftMotor, 1000, 2000);
  servoRight.attach(rightMotor, 1000, 2000);

  servoLeft.write(90);
  servoRight.write(90);
}

void Motors::update() {
  setMotorRight(targetR);
  setMotorLeft(targetL);
}

void Motors::setMotorLeft(int speed) {
  if (!setUp) {
    return;
  }

  //Clamp the speed between -100 and 100
  if (speed > 100) {
    speed = 100;
  }
  if (speed < -100) {
    speed = -100;
  }

  if (targetL != speed) { // We found a new speed to ahead towards
    // Reset variables
    targetL = speed;
    startSpeedL = curSpeedL;
    curTicksL = 1;

    // Begin lerp towards new speed
    curSpeedL = lerp(startSpeedL, speed, ((double)curTicksL)/lerpTime);
    servoLeft.write(90 + (curSpeedL * speedRatio));
  } else if (curSpeedL != speed) { //We are already on course to a new speed

    curTicksL = curTicksL + 1;
    if (curTicksL == lerpTime) {
      curSpeedL = speed;
    } else {
      curSpeedL = lerp(startSpeedL, speed, ((double)curTicksL)/lerpTime); // Lerp towards target speed
    }
    servoLeft.write(90 + (curSpeedL * speedRatio));
  }
}

void Motors::setMotorRight(int speed) {

  if (!setUp) {
    return;
  }

  if (speed > 100) {
    speed = 100;
  }
  if (speed < -100) {
    speed = -100;
  }

  //Clamp the speed between -100 and 100
  if (targetR != speed) { // We found a new speed to ahead towards
    // Reset variables
    targetR = speed;
    startSpeedR = curSpeedR;
    curTicksR = 1;

    // Begin lerp towards new speed
    curSpeedR = lerp(startSpeedR, speed, ((double)curTicksR)/lerpTime);
    servoRight.write(90 + (curSpeedR * speedRatio));
  } else if (curSpeedR != speed) { // We are already on course to a new speed

    curTicksR = curTicksR + 1;
    if (curTicksR == lerpTime) {
      curSpeedR = speed;
    } else {
      curSpeedR = lerp(startSpeedR, speed, ((double)curTicksR)/lerpTime); // Lerp towards target speed
    }
    servoRight.write(90 + (curSpeedR * speedRatio));
  }
}

void Motors::setBothMotors(int speed) {
  setMotorLeft(speed);
  setMotorRight(speed);
}


int Motors::lerp(int start, int end, double fraction) {
  return (int)(start + (end - start) * fraction); //linear interpolation
}