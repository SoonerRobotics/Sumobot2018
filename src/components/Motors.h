#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Servo.h>

class Motors {
public:

  double const speedRatio = 90.0/100.0;

  void init(int leftMotor, int rightMotor);

  void setMotorLeft(int speed);
  void setMotorRight(int speed);
  void setBothMotors(int speed);

private:

  bool setUp = false;
  Servo servoLeft;
  Servo servoRight;

};

#endif
