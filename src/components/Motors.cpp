#include "motors.h"

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

  double outputSpeed = 90 + (speed * speedRatio);

  servoLeft.write(outputSpeed);
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


  double outputSpeed = 90 + (speed * speedRatio);

  servoRight.write(outputSpeed);
}

void Motors::setBothMotors(int speed) {
  setMotorLeft(speed);
  setMotorRight(speed);
}
