#include "Servo.h"

Servo myservo;  // create servo object to control a servo
//const int serial_INPUT = 19;    // Digital output
//const int serial1_OUTPUT = 18;
//const int PWM_PIN = 2;  // Digital input
//const int SENSORPIN = 0; // Analog input
//int pos = 0;    // variable to store the servo position
//bool isexecuted = false;
const int min = 23;
const int standard = 63;
const int max = 108;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(standard);
  Serial.begin(9600); // Corrected to Serial
  while (!Serial) { ; } // Wait for Serial to initialize
  Serial.setTimeout(50);
}

void loop() {
  if (Serial.available() > 0) {
    int serialInput = Serial.readString().toInt();  // Read one byte of input
    if(serialInput > max){
      serialInput = max;
    }
    if(serialInput < min){
      serialInput = min;
    }
      myservo.write(serialInput);  // Write the value to the servo
  }
}
  