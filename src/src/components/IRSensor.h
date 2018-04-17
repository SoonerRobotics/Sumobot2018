#ifndef SUMO_COMPONENTS_IRSENSOR_H_
#define SUMO_COMPONENTS_IRSENSOR_H_

class IRSensor {
public:
  void init(int _pin);

  void update();

  double getDistanceNow();

  double getDistance();

  double getAverage();

  double getMedian();

private:

    double last5[5] = {0, 0, 0, 0 ,0};

    bool setUp = false;
    int pin = -1;
};

#endif