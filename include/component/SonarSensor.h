#pragma once

#include <Arduino.h>

class SonarSensor {
  byte trigger;
  byte echo;
  long distance = 0;

  long readDistance() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    return pulseIn(echo, HIGH)/58;
  }
public:
  SonarSensor(byte trigger, byte echo) {
    this->trigger = trigger;
    this->echo = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  void scan() {
    distance = readDistance();
  }

  long isInRange(int range) {
    return (distance > 0 && distance <= range) ? distance : 0;
  }
};

