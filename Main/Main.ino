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
  long lastAction;
  Motor motor(dacPin, DIRECTION_PIN, minSpeed, maxSpeed);
  Steering steering(SteeringAnglePin, min, standard, max);
  // M=100
  // S=50
  // B=50

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) { ; } 
  motor.begin();
  steering.begin();
  Serial.setTimeout(10);
  lastAction = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    if(millis() - lastAction > 200){
      reset();
    }
    String serialInput = Serial.readString();
    parseInput(serialInput);
    
  }else{
      reset();
  }
}
void reset(){
  motor.setSpeed(0);
  steering.update(0);
}

void parseInput(String input) {
    // Splits de string op basis van de komma
    int commaIndex = input.indexOf(',');
    while (commaIndex != -1) {
        String pair = input.substring(0, commaIndex); // Haal het paar voor de komma
        handlePair(pair); // Verwerk het paar
        input = input.substring(commaIndex + 1); // Verwijder het verwerkte paar
        commaIndex = input.indexOf(','); // Zoek de volgende komma
    }
    // Verwerk het laatste paar (of het enige paar als er geen komma's zijn)
    handlePair(input);
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
            motor.setSpeed(intValue);
            lastAction = millis();
        } else if (key == "S") {
            steering.update(intValue);
            lastAction = millis();
        } else if (key == "B") {
            int B = intValue;
            Serial.print("B is ingesteld op: ");
            Serial.println(B);
            lastAction = millis();
        } else {
            Serial.print("Ongeldige sleutel: ");
            Serial.println(key);
        }
    } else {
        Serial.println("Ongeldige invoer. Zorg ervoor dat de waarden in het juiste formaat zijn.");
    }
}


