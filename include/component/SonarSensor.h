#pragma once

#ifdef NEW_PING

#include <NewPing.h>
#include "SonarObstacle.h"

#define MAX_DISTANCE 100

class SonarSensor {
  NewPing* sonar;

public:

  SonarSensor(uint8_t trigger, uint8_t echo) {
    sonar = new NewPing(trigger, echo, MAX_DISTANCE);
  }

  SonarObstacle* scan() {
    unsigned long time = millis();
    long distance = sonar->convert_cm(sonar->ping_median());
    return new SonarObstacle(distance, time);
  }
};

#else

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

#endif