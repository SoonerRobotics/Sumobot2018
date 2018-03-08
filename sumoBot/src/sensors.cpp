#include <Arduino.h>

class IRSensor {
  
public:

  double last5[5] = {0, 0, 0, 0 ,0};
  bool setUp = false;
  int pin = -1;

  double const speedRatio = 90.0/100.0;
  void init(int _pin) 
  {
    if (setUp) 
    {
      return;
    }
    setUp = true;
    pin = _pin;
    pinMode(pin, OUTPUT);
  }

  void update() 
  {
    last5[4] = last5[3];
    last5[3] = last5[2];
    last5[2] = last5[1];
    last5[1] = last5[0];
    last5[0] = getDistanceNow();
  }
  double getDistanceNow()
  {
    float volts = analogRead(pin)*0.0048828125;  // value from sensor * (5/1024)
    double distance = 12 * 2.54 *pow(volts, -1); // worked out from datasheet graph
    return distance;
  }

  double getDistance() 
  { // average of the last 5 distances
  double sum = last5[4] + last5[3] + last5[2] + last5[1] + last5[0];
  return sum/5; // possibly use median insteadd of average
  }
};

class lineSensor {
  public:
    bool setUp = false;
    int pin = -1;
    int lineValue = 0;
  void init(int newPin){
        if (setUp){
          return;  
        }
        setUp = true;
        pin = newPin;
        pinMode(pin, OUTPUT);
  }
  bool isValue(){
    if (lineValue >950) return false;
    else return true;
    
  }  
  void update(){
    lineValue = analogRead(pin);
  }
};
class ledArray {
public:
  bool setUp = false;
  int pin0, pin1, pin2 = -1;
void init(int newPin0, int newPin1, int newPin2){
        if (setUp){
          return;  
        }
        setUp = true;
        pin0 = newPin0;
        pin1 = newPin1;
        pin2 = newPin2;
        pinMode(pin0, OUTPUT);
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
  }

void lightUp(int ledNum){
    switch(ledNum)
    {
    case 0:
      digitalWrite(pin0, LOW);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      break;
    case 1:
      digitalWrite(pin0, LOW);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      break;
    case 2:
      digitalWrite(pin0, LOW);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      break;
    case 3:
      digitalWrite(pin0, LOW);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      break;
    case 4:
      digitalWrite(pin0, HIGH);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      break;
    case 5:
      digitalWrite(pin0, HIGH);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      break;
    case 6:
      digitalWrite(pin0, HIGH);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      break;
    case 7:
      digitalWrite(pin0, HIGH);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      break;
    default:
      Serial.print("something broke");
      ledNum = 0;
      break;
    }
  }
  

};


