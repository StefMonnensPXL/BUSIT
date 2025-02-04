// Motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int pwmPin, int dirPin, int minSpeed, int maxSpeed);
    void begin();
    int setSpeed(int speed);
    void update();

private:
    int _pwmPin;
    int _dirPin;
    int _minSpeed;
    int _maxSpeed;
    int _lastDirection;
    int _currentSpeed;
};

#endif // MOTOR_H