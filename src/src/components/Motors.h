#ifndef SUMO_COMPONENTS_MOTORS_H_
#define SUMO_COMPONENTS_MOTORS_H_

#include <Servo.h>

class Motors {
public:

  double const speedRatio = 90.0/100.0;
  int const lerpTime = 8; //ticks

  void init(int leftMotor, int rightMotor);

  void setMotorLeft(int speed);
  void setMotorRight(int speed);
  void setBothMotors(int speed);

private:

  bool setUp = false;
  Servo servoLeft;
  Servo servoRight;

  int targetL = 0;
  int curSpeedL = 0;
  int curTicksL = 0;
  int startSpeedL = 0;

  int targetR = 0;
  int curSpeedR = 0;
  int curTicksR = 0;
  int startSpeedR = 0;

  int lerp(int start, int end, double fraction);

};

#endif
