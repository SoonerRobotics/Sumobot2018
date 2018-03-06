#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <Arduino.h>

class LineFollower {
public:
  void init(int _pin);

  bool seeLine();

private:

    bool setUp = false;
    int pin = -1;
};

#endif