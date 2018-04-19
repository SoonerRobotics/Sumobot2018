#include "motors.h"

#include <Arduino.h>

void Motors::init(int leftMotor, int rightMotor) {

  if (setUp) {
    return;
  }

  setUp = true;

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

  if (speed > 100) {
    speed = 100;
  }
  if (speed < -100) {
    speed = -100;
  }

  if (targetL != speed) { //new setMotorCommand
    targetL = speed;
    startSpeedL = curSpeedL;
    curTicksL = 1;
    curSpeedL = lerp(startSpeedL, speed, ((double)curTicksL)/lerpTime);
    servoLeft.write(90 + (curSpeedL * speedRatio));
  } else if (curSpeedL != speed) {
    curTicksL = curTicksL + 1;
    if (curTicksL == lerpTime) {
      curSpeedL = speed;
    } else {
      curSpeedL = lerp(startSpeedL, speed, ((double)curTicksL)/lerpTime);
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

  if (targetR != speed) { //new setMotorCommand
    targetR = speed;
    startSpeedR = curSpeedR;
    curTicksR = 1;
    curSpeedR = lerp(startSpeedR, speed, ((double)curTicksR)/lerpTime);
    servoRight.write(90 + (curSpeedR * speedRatio));
  } else if (curSpeedR != speed) {
    curTicksR = curTicksR + 1;
    if (curTicksR == lerpTime) {
      curSpeedR = speed;
    } else {
      curSpeedR = lerp(startSpeedR, speed, ((double)curTicksR)/lerpTime);
    }
    servoRight.write(90 + (curSpeedR * speedRatio));
  }
}

void Motors::setBothMotors(int speed) {
  setMotorLeft(speed);
  setMotorRight(speed);
}


int Motors::lerp(int start, int end, double fraction) {
  return (int)(start + (end - start) * fraction);
}