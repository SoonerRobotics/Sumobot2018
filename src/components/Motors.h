#ifndef SUMO_COMPONENTS_MOTORS_H_
#define SUMO_COMPONENTS_MOTORS_H_

#include <Servo.h>

class Motors {
public:

  double const speedRatio = 90.0/100.0; // The scale factor between the range of speeds and 180
  int const lerpTime = 12; // How many "tick"s to lerp over

  void init(int leftMotor, int rightMotor);

  void update(); // Should be called every "tick" to keep the motors lerping towards desired speed
  void setMotorLeft(int speed); // Set the speed of the left motor from -100 to 100
  void setMotorRight(int speed); // Set the speed of the right motor from -100 to 100
  void setBothMotors(int speed); // Set the speed of both motors from -100 to 100

private:

  bool setUp = false; // If init has been called
  Servo servoLeft; // The servo controlling the left motor
  Servo servoRight; // The servo controlling the right motor

  int targetL = 0; // The desired speed of the left motor
  int curSpeedL = 0; // The current speed of the left motor
  int curTicksL = 0; // The current amount of "tick"s since the last target change
  int startSpeedL = 0; // The speed at the time of the last target change

  int targetR = 0; // The desired speed of the right motor
  int curSpeedR = 0; // The current speed of the right motor
  int curTicksR = 0; // The current amount of "tick"s since the last target change
  int startSpeedR = 0; // The speed at the time of the last target chagne

  int lerp(int start, int end, double fraction); // Linear interpolation from start to end

};

#endif
