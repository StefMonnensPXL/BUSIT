#include "Servo.h"

  Servo myservo;  // create servo object to control a servo
  const int dacPin = DAC1;  // Pin 2 op de Arduino Due is een echte DAC
  int outputValue = 0;    // Variabele om de waarde van de DAC uit te sturen (0-4095)
  const int DIRECTION_PIN = 50;
  const int min = -200;
  const int max = 200;


void setup() {
  pinMode(DIRECTION_PIN, OUTPUT);
  //pinMode(DIRECTION_PIN, HIGH);
  Serial.begin(9600); // Corrected to Serial
  while (!Serial) { ; } // Wait for Serial to initialize
  Serial.setTimeout(50);
  analogWrite(dacPin, 0);
}

void loop() {
  if(Serial.available() > 0){
    int serialInput = Serial.readString().toInt() * 2;
    if(serialInput > max){
      serialInput = max;
    }
    if(serialInput < min){
      serialInput = min;
    }
    if(serialInput < 0){
      digitalWrite(DIRECTION_PIN, LOW);
    }else{
      digitalWrite(DIRECTION_PIN, HIGH);
    }
    analogWrite(dacPin, abs(serialInput));
    Serial.println(serialInput);
  }
  delay(1000);  // Wacht 1 seconde voordat de waarde opnieuw stijgt
}
