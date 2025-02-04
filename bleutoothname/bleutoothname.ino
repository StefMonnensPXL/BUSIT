//  SerialIn_SerialOut_HM-10_Arduino_Due
//
//  Uses hardware serial (Serial3) to communicate with the Bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 3.3V out. 
//  BT GND to GND
//  Arduino Due TX3 (pin 14) - BT RX through a voltage divider (3.3V logic level)
//  Arduino Due RX3 (pin 15) - BT TX (3.3V safe)

char c = ' ';
boolean NL = true;

void setup() 
{
    Serial.begin(9600);


    Serial3.begin(9600);  // Using Serial3 for Bluetooth communication
    Serial.println("Serial3 (BTserial) started at 9600");
}

void loop()
{
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (Serial3.available())
    {
        c = Serial3.read();
        Serial.write(c);
    }

    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();

        // Do not send line end characters to the HM-10
        if (c != 10 && c != 13) 
        {
            Serial3.write(c);
        }

        // Echo the user input to the main window.
        // If there is a new line, print the ">" character.
        if (NL) { Serial.print("\r\n>");  NL = false; }
        Serial.write(c);
        if (c == 10) { NL = true; }
    }
}