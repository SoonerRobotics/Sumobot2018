#include "IRSensor.h"

#include <Arduino.h>

void IRSensor::init(int _pin) {

  if (setUp) {
    return;
  }

  setUp = true;

  pin = _pin;
  
  pinMode(pin, OUTPUT);
}

void IRSensor::update() {
  last5[4] = last5[3];
  last5[3] = last5[2];
  last5[2] = last5[1];
  last5[1] = last5[0];
  last5[0] = getDistanceNow();
}

double IRSensor::getDistanceNow() {
  float volts = analogRead(pin)*0.0048828125;  // value from sensor * (5/1024)
  double distance = 12 * 2.54 *pow(volts, -1); // worked out from datasheet graph
  return distance;
}

double IRSensor::getDistance() {
  return getAverage();
}

double IRSensor::getAverage() {
    double sum = last5[4] + last5[3] + last5[2] + last5[1] + last5[0];
    return sum/5;
}

double IRSensor::getMedian() {
  //TODO
  return 0.0;
}
