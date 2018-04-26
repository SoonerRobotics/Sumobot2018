#ifndef SUMO_COMPONENTS_IRSENSOR_H_
#define SUMO_COMPONENTS_IRSENSOR_H_

class IRSensor {
public:
  void init(int _pin); // Initalize the IR Sensor on a certain pin

  void update();  // Should be called every "tick", updates the IR Sensor data
                  // Called every tick for purposes of taking an average

  double getDistanceNow(); // Returns the exact value of the IR Sensor at the given moment

  double getDistance(); // Returns the value of the IR Sensor averaged over the last 5 "tick"s

private:

    double last5[5] = {0, 0, 0, 0 ,0}; // The values of the IR Sensor on the last 5 "tick"s

    bool setUp = false; // If the init method has been called
    int pin = -1; // The pin the IR Sensor reads from

    double getAverage(); // Get the average of the last5 values

    double getMedian(); // Get the median of the last5 values
};

#endif