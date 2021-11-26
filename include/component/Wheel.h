#pragma once
#include <Arduino.h>
#define DEFAULT_WHEEL_SPEED 200

class Wheel {
  byte pin1;
  byte pin2;
  byte speedPin;
  byte speed;
public:
  Wheel(byte pin1, byte pin2, byte speedPin, byte speed) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->speedPin = speedPin;
    this->speed = speed;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(speedPin, OUTPUT);
  }

  void stop() {
    digitalWrite(speedPin, HIGH);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  void forward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedPin, speed);
  }

  void backward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedPin, speed);
  }
};
