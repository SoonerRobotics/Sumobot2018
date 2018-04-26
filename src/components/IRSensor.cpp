#include "IRSensor.h"

#include <Arduino.h>

void IRSensor::init(int _pin) {

  if (setUp) {
    return;
  }

  setUp = true;

  pin = _pin;
  
  pinMode(pin, INPUT);
}

void IRSensor::update() {
  last5[4] = last5[3];
  last5[3] = last5[2];
  last5[2] = last5[1];
  last5[1] = last5[0];
  last5[0] = getDistanceNow();
}

double IRSensor::getDistanceNow() {
  // Transform the analog input into a scale of 0.0 - 5.0 V
  // By multiplying by (5.0/1024.0)
  float volts = analogRead(pin) * 0.0048828125;
  return 42*pow(volts, -1); // worked out from datasheet graph
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
