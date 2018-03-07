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

//TODO: Lerp
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

//TODO: Lerp
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
  if (target != speed) { //new setMotorCommand
    target = speed;
    startSpeed = curSpeed;
    curTicks = 1;
    curSpeed = lerp(startSpeed, speed, curTicks/lerpTime);
    setMotorLeft(curSpeed);
    setMotorRight(curSpeed);
  } else if (curSpeed != speed) {
    curTicks += curTicks + 1;
    if (curTicks == lerpTime) {
      curSpeed = speed;
    } else {
      curSpeed = lerp(startSpeed, speed, curTicks/lerpTime);
    }
    setMotorLeft(curSpeed);
    setMotorRight(curSpeed);
  }
}


int Motors::lerp(int start, int end, double fraction) {
  return (int)((end - start) * fraction + start);
}