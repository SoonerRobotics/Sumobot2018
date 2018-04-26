#ifndef SUMO_COMPONENTS_MAGNETS_H_
#define SUMO_COMPONENTS_MAGNETS_H_

class Magnets {
public:
  void init(int _pin); // Initialize the Magnets on a certain pin

  void setState(bool on); // Set the Magnets on or off

private:

    bool setUp = false; // If init has been called
    int pin = -1; // The pin Magnets are controlled on 

    bool isOn = false; // If the Magnets are currently on
};

#endif