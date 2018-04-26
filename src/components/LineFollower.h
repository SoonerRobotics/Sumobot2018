#ifndef SUMO_COMPONENTS_LINEFOLLOWER_H_
#define SUMO_COMPONENTS_LINEFOLLOWER_H_

class LineFollower {
public:
  void init(int _pin); // Initialize the line follower on a certain pin
  void init(int _pin, int _sensitivity); // Initialize the line follower on a certain pin

  bool seeLine(); // If the line follower is currently detecting a white line

private:

    int sensitivity = 200; // When the line follower detects values above this, seeLine() is true

    bool setUp = false; // If init has been called
    int pin = -1; // The pin for this instance of a line follower
};

#endif