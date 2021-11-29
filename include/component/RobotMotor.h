#pragma once

#ifndef PROTOTYPE

#include <Arduino.h>
#include "Motor.h"

class PrototypeMotor : public Motor {

public:
  PrototypeMotor(uint8_t pin1, uint8_t pin2) : Motor(pin1, pin2) {
  }

  void stop() override {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  void forward() override {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  void backward() override {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
} 
left(LEFT_WHEEL_BACKWARD, LEFT_WHEEL_FORWARD), 
right(RIGHT_WHEEL_BACKWARD, RIGHT_WHEEL_FORWARD);

#endif
