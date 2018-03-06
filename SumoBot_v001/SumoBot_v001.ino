#include "motors.cpp"
#include "sensors.cpp"

enum State {start, wait, forward, backwards, searchLeft, searchRight, stall};

Motors motors; // creates motors object for left and right motors
IRSensor leftSensor;
IRSensor rightSensor;

void setup() {
  Serial.begin(9600);

  motors.init(9, 10);
  leftSensor.init(2);
  rightSensor.init(3);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
 switch (state){
    //************Start************
    case start :
      //State Action
      
        state = wait; 
      break;
   case default : 
    Serial.println("darn");
    break;
 }


  
/*
  float volts = analogRead(2)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 12 * 2.54 *pow(volts, -1); // worked out from datasheet graph

  if (distance < 10 ) {
    motors.setMotorLeft(0);
    motors.setMotorLeft(0);
  }
  else {
    motors.setMotorLeft(100);
    motors.setMotorLeft(100);
  }
  delay(100);
  */
}
