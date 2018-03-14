#ifndef SUMO_COMPONENTS_LINEFOLLOWER_H_
#define SUMO_COMPONENTS_LINEFOLLOWER_H_

class LineFollower {
public:
  void init(int _pin);

  bool seeLine();

private:

    bool setUp = false;
    int pin = -1;
};

#endif