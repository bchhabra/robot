#pragma once

#ifndef NEW_PING

#include "SonarObstacle.h"

class SonarSensor {
  uint8_t trigger;
  uint8_t echo;

  long readDistance() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    return pulseIn(echo, HIGH)/58;
  }
public:
  SonarSensor(uint8_t trigger, uint8_t echo) {
    this->trigger = trigger;
    this->echo = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  void scan(SonarObstacle& obstacle) {
    obstacle.setValues(readDistance(), millis());
  }
};

#endif
