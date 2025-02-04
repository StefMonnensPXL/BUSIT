// ServoController.cpp
#include "Steering.h"


Steering::Steering(int pin, int min, int standard, int max)
    : _pin(pin), _min(min), _standard(standard), _max(max) {}

void Steering::begin() {
    _servo.attach(_pin);
    _servo.write(_standard);
    
}

int Steering::update(int angle) {
    angle = convertAngle(angle);
        if (angle > _max) {
            angle = _max;
        }
        if (angle < _min) {
            angle = _min;
        }
        _servo.write(angle);
        return(angle);
}

int Steering::convertAngle(int angle) { 
    if (angle < 0) {
        return _standard + angle;
    } else if (angle > 0) {
        return _standard + static_cast<int>((static_cast<double>(angle) / 40.0) * (_max - _standard));
    }
    return _standard;  // Als angle == 0, blijft het de standaardwaarde
}

