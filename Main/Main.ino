#include "Motor.h"
#include "Steering.h"
  const int dacPin = DAC1;
  const int DIRECTION_PIN = 50;
  const int SteeringAnglePin = 9; 
  const int minSpeed = -200;
  const int maxSpeed = 200;
  const int min = 23;
  const int standard = 63;
  const int max = 108;
  Motor motor(dacPin, DIRECTION_PIN, minSpeed, maxSpeed);
  Steering steering(SteeringAnglePin, min, standard, max);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) { ; } 
  motor.begin();
  //steering.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int serialInput = Serial.readString().toInt();
    motor.setSpeed(serialInput);
    //Serial.println(steering.update(serialInput));
   
  }
  
}
