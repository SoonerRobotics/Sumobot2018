#include <Arduino.h>
#include <Servo.h>

class Motors {
public:

  bool setUp = false;

  Servo servoLeft;
  Servo servoRight;

  double const speedRatio = 90.0/100.0;

  void init(int leftMotor, int rightMotor) {

    if (setUp) {
      return;
    }

    setUp = true;
    
    servoLeft.attach(leftMotor, 1000, 2000);
    servoRight.attach(rightMotor, 1000, 2000);

    servoLeft.write(90);
    servoRight.write(90);
  }

  void setMotorLeft(int speed) {

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

  void setBothMotors(int speed) {

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
    servoRight.write(outputSpeed);
  }
  
  
};
