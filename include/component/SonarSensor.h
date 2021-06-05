#pragma once

#include "SonarObstacle.h"

#ifdef NEW_PING

#include <NewPing.h>

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

  SonarObstacle* scan() {
    return new SonarObstacle(readDistance(), millis());
  }
};

#endif
