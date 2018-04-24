#ifndef SUMO_COMPONENTS_MAGNETS_H_
#define SUMO_COMPONENTS_MAGNETS_H_

class Magnets {
public:
  void init(int _pin);

  void setState(bool on);

private:

    bool setUp = false;
    int pin = -1;

    bool isOn = false;
};

#endif