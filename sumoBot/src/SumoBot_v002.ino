#include "motors.cpp"
#include "sensors.cpp"
# define x 0
# define y 0
# define z 0
# define a 0
enum State {start, forward, forwardx, backwards, searchLeft, searchRight, stall};

Motors motors; // creates motors object for left and right motors
IRSensor leftSensor;
IRSensor rightSensor;
lineSensor line0;
lineSensor line1;

bool white0 = false;
bool white1 = false;
bool white = false;

State state = start;

void setup() {
  Serial.begin(9600);

  motors.init(9, 10);
  leftSensor.init(2);
  rightSensor.init(3);
  line0.init(0);
  line1.init(1);
  
  
}

long startTime = -1;
long waitTime = 0;
boolean smartWait(long timeToWait) {
    if (startTime < 0) { //new smartWait task
        startTime = millis();
        waitTime = timeToWait;
    } else {
        if (millis() - startTime > timeToWait) {
            startTime = -1;
            return true;
        }
    }
    return false;
}

void startSequence(){
  delay(x);
  state = forwardx;   
  }
void forwardxSequence(){
    motors.setBothMotors(100);
    if(!smartWait(y)) return;
    state = forward;
  }
void forwardSequence(){
  motors.setBothMotors(25);
   if(line0.isValue() || line1.isValue()){
      stopSequence();
      delay(1000);
      state = backwards; 
    }
  
  }
  
void backwardsSequence(){
  motors.setBothMotors(-100);
  delay(1000);
  state = forward; 
  }
  
void searchLeftSequence(){}

void searchRightSequence(){}

void stallSequence(){}

void stopSequence() {
  motors.setBothMotors(0);
  }

void electroMagnet(bool onOff){}

void updateSensors(){
  line0.update();
  line1.update();

}




void loop() {

updateSensors();

// if(!smartWait(1000)) return;  
 switch (state){
  case start : startSequence(); break;
      
  case forwardx : forwardxSequence(); break;
    
  case forward : forwardSequence(); break;
    
  case backwards :backwardsSequence(); break;
    
  case searchLeft : state = searchRight; break;
    
  case searchRight : state = stall; break;
    
  case stall : break;
    
  default: Serial.println("darn"); break;
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
