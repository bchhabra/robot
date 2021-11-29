#pragma once

#ifdef PROTOTYPE

#include <Arduino.h>
#include "Motor.h"

#define DEFAULT_WHEEL_SPEED 200

class PrototypeMotor : public Motor {

  uint8_t speedPin;
  uint8_t speed;

public:
  PrototypeMotor(uint8_t pin1, uint8_t pin2, uint8_t speedPin, uint8_t speed) : Motor(pin1, pin2) {
    this->speedPin = speedPin;
    this->speed = speed;
    pinMode(speedPin, OUTPUT);
  }

  void stop() override {
    digitalWrite(speedPin, HIGH);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  void forward() override {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedPin, speed);
  }

  void backward() override {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedPin, speed);
  }
} 
left(LEFT_WHEEL_BACKWARD, LEFT_WHEEL_FORWARD, LEFT_WHEEL_SPEED, 150), 
right(RIGHT_WHEEL_BACKWARD, RIGHT_WHEEL_FORWARD, RIGHT_WHEEL_SPEED, 180);

#endif
