// ServoController.h
#ifndef STEERING_H
#define STEERING_H
#include <Arduino.h>
#include <Servo.h>


class Steering {
public:
    Steering(int pin, int min, int standard, int max);
    void begin();
    int update(int angle);

private:
    ::Servo _servo;
    int _pin;
    int _min;
    int _standard;
    int _max;
};

#endif // SERVOCONTROLLER_H