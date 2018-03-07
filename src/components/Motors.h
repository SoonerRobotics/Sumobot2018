#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Servo.h>

class Motors {
public:

  double const speedRatio = 90.0/100.0;
  double const lerpTime = 8; //ticks

  void init(int leftMotor, int rightMotor);

  void setMotorLeft(int speed);
  void setMotorRight(int speed);
  void setBothMotors(int speed);

private:

  bool setUp = false;
  Servo servoLeft;
  Servo servoRight;

  int target = 0;
  int curSpeed;
  int curTicks;
  int startSpeed;

  int lerp(int start, int end, double fraction);

};

#endif
