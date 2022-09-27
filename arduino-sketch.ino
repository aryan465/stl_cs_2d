// Program for working of stepper motors
// Board used is Arduino Mega
 
#include <Stepper.h>
#define STEPS_PER_REV =  200;
 
// if using Potentiometer
const int SPEED_CONTROL = A0;
 
Stepper motor1(STEPS_PER_REV,8,9,10,11);
Stepper motor2(STEPS_PER_REV,4,5,6,7);
Stepper motor3(STEPS_PER_REV,22,23,24,25);
Stepper motor4(STEPS_PER_REV,27,28,29,30);
 
void setup() {
  // Setting motor speed in rpm
  motor1.setSpeed(10);
  motor2.setSpeed(10);
  motor3.setSpeed(10);
  motor4.setSpeed(10);
 
  // Serial port to read data
  Serial.begin(9600);
}
 
// data array will contain the amount of linear motion(in mm) for each block
// In this code 4 stepper motors are configured and used.
// It can be further extended to as many stepper motors as the number of blocks in the mechanism.

String data[4];
int index = 0;
int steps = 0;
 
void loop() {
  // Reading from Serial port
  if(Serial.available()){
    data[index] = Serial.readStringUntil(',');
    // printing it to visualize
    Serial.print("data");
    Serial.println(index+1);
    Serial.println(": ");
    Serial.println(data[index]);
    index++;
 
    if (index==4){
      index = 0;
 
  // if using Potentiometer to control motor speed
    int reading = analogRead(SPEED_CONTROL);
      // converting the speed range to (0,100)
    int motorSpeed = map(reading,0,1023,0,100);
 
  // setting motor speed for each stepper motor 
    motor1.setSpeed(motorSpeed);
    motor2.setSpeed(motorSpeed);
    motor3.setSpeed(motorSpeed);
    motor4.setSpeed(motorSpeed);
  // over
  // steps to turn the motor
  // assuming 1 step (1.8 deg.) = 0.5 mm in linear motion
  // the gears will be designed considering this ratio
 
 
  steps = (data[0].toInt())*2;
  motor1.step(steps);
  steps = (data[1].toInt())*2;
  motor2.step(steps);
  steps = (data[2].toInt())*2;
  motor3.step(steps);
  steps = (data[3].toInt())*2;
  motor4.step(steps);
    }
  }
 
}
