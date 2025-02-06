#include "Motor.h"
#include "Steering.h"
  const int dacPin = DAC1;
  const int DIRECTION_PIN = 50;
  const int SteeringAnglePin = 9; 
  const int minSpeed = -200;
  const int maxSpeed = 200;
  const int min = 44;
  const int standard = 84;
  const int max = 124;
  long lastAction;
  Motor motor(dacPin, DIRECTION_PIN, minSpeed, maxSpeed);
  Steering steering(SteeringAnglePin, min, standard, max);
  // M=100
  // S=50
  // B=50

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);
  while (!Serial) { ; } 
  motor.begin();
  steering.begin();
  Serial.setTimeout(10);
  Serial3.setTimeout(10);
  
  lastAction = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
    
    if(millis() - lastAction > 1000){
      reset();
    }
    String serialInput = Serial3.readString();
    parseInput(serialInput);
}
void reset(){
  motor.setSpeed(0);
  steering.update(0);
}

void parseInput(String input) {
    int commaIndex = input.indexOf(',');
    while (commaIndex != -1) {
        String pair = input.substring(0, commaIndex);
        handlePair(pair);
        input = input.substring(commaIndex + 1);
        commaIndex = input.indexOf(',');
    }
    if (input.length() > 0) {  // Process the last remaining pair
        handlePair(input);
    }
}

void handlePair(String pair) {
    // Zoek de positie van het '=' teken
    int equalsIndex = pair.indexOf('=');
    
    
    if (equalsIndex != -1) {
        String key = pair.substring(0, equalsIndex); // Haal de sleutel (M, S, B)
        String value = pair.substring(equalsIndex + 1); // Haal de waarde

        // Zet de waarde om naar een integer
        int intValue = value.toInt();

        // Controleer de eerste letter en handel de waarde af
        if (key == "M") {
            Serial.println(motor.setSpeed(intValue));
            lastAction = millis();
        ;} else if (key == "R") {
            steering.update(intValue);
            lastAction = millis();
        } else {
            Serial.print("Ongeldige sleutel: ");
            Serial.println(key);
        }
    }
}


