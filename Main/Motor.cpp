// Motor.cpp
#include "Motor.h"


Motor::Motor(int pwmPin, int dirPin, int minSpeed, int maxSpeed) 
    : _pwmPin(pwmPin), _dirPin(dirPin), _minSpeed(minSpeed), _maxSpeed(maxSpeed), _lastDirection(HIGH), _currentSpeed(0) {}

void Motor::begin() {
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    digitalWrite(_dirPin, LOW);
    analogWrite(_pwmPin, 0);
}

int Motor::setSpeed(int speed) {
    if(speed > 0) speed = speed + 100;
    if(speed < 0) speed = speed - 100;
    if (speed > _maxSpeed) speed = _maxSpeed;
    if (speed < _minSpeed) speed = _minSpeed;
    int newDirection = (speed > 0) ? HIGH : LOW;
    if (newDirection != _lastDirection) {
        analogWrite(_pwmPin, 0);
        delay(375);
        digitalWrite(_dirPin, newDirection);
        delay(375);
        _lastDirection = newDirection;
    }
    analogWrite(_pwmPin, abs(speed));
    return(abs(speed));
}

void Motor::update() {
    analogWrite(_pwmPin, _currentSpeed);
}
