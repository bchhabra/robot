#pragma once

#ifdef NEW_PING

#include <NewPing.h>
#include "Obstacle.h"

class SonarSensor {
  NewPing* sonar;
  long distance = 0;
  Direction direction;

public:

  SonarSensor(uint8_t trigger, uint8_t echo, Direction direction) {
    sonar = new NewPing(trigger, echo, 200);
    this->direction = direction;
  }

  Obstacle* scan() {
    unsigned long time = millis();
    distance = sonar->convert_cm(sonar->ping_median());
    return distance == 0 ? NULL : new Obstacle(distance, time, direction);
  }

  long isInRange(int range) {
    return (distance > 0 && distance <= range) ? distance : 0;
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