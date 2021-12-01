#pragma once

#include "Obstacle.h"

#define OBSTACLE_RANGE 20

class SonarObstacle : public Obstacle {

public:
  long distance = 0;

  void setValues(long distance, unsigned long time) {
    this->distance = distance;
    this->time = time;
  }

  bool isInRange(int range) {
    return (distance > 0 && distance <= range);
  }
};
