#include <Arduino.h>

class IRSensor {
public:

  double last5[5] = {0, 0, 0, 0 ,0};
  bool setUp = false;
  int pin = -1;

  double const speedRatio = 90.0/100.0;
  void init(int _pin) {
    if (setUp) {
      return;
    }
    setUp = true;
    pin = _pin;
    pinMode(pin, OUTPUT);
  }

  double update() {
    last5[4] = last5[3];
    last5[3] = last5[2];
    last5[2] = last5[1];
    last5[1] = last5[0];
    last5[0] = getDistanceNow();
  }

  double getDistanceNow() {
    float volts = analogRead(pin)*0.0048828125;  // value from sensor * (5/1024)
    double distance = 12 * 2.54 *pow(volts, -1); // worked out from datasheet graph
    return distance;
  }

  double getDistance() { // average of the last 5 distances
    double sum = last5[4] + last5[3] + last5[2] + last5[1] + last5[0];
      return sum/5; // possibly use median insteadd of average
  }
  


};
