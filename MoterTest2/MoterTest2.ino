#include "Servo.h"
  //const int dacPin = DAC1; -> praktijk
  //const int DIRECTION_PIN = 50; -> praktijk
Servo myservo;  
const int pwmPin = 9;  // Virtueel
const int DIRECTION_PIN = 7;  // Virtueel
const int minSpeed = -200;
const int maxSpeed = 200;
int lastDirection = HIGH; 

void setup() {
  pinMode(DIRECTION_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) { ; } 
  Serial.setTimeout(50);
  analogWrite(pwmPin, 0);
}

void loop() {
  if (Serial.available() > 0) {
    int serialInput = Serial.readString().toInt() * 2;
    
    if (serialInput > maxSpeed) serialInput = maxSpeed;
    if (serialInput < minSpeed) serialInput = minSpeed;
    
    int newDirection = (serialInput < 0) ? LOW : HIGH;
    if (newDirection != lastDirection) {
      delay(500);
      analogWrite(pwmPin, 0);
      delay(500);
      digitalWrite(DIRECTION_PIN, newDirection);
      lastDirection = newDirection;
    }
    
    analogWrite(pwmPin, abs(serialInput) / 2);  // PWM-waarde aanpassen
    Serial.println(serialInput);
  }
  delay(1000);
}
