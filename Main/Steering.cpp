// ServoController.cpp
#include "Steering.h"
#include <Servo.h>

Steering::Steering(int pin, int min, int standard, int max)
    : _pin(pin), _min(min), _standard(standard), _max(max) {}

void Steering::begin() {
    _servo.attach(_pin);
    _servo.write(_standard);
    
}

int Steering::update(int angle) {
    if (angle > 0) {
        if (angle > _max) {
            angle = _max;
        }
        if (angle < _min) {
            angle = _min;
        }
        _servo.write(angle);
        return(angle);
    }
}

