#pragma once

#include "Obstacle.h"

class SonarObstacle : public Obstacle {

public:
  long distance = 0;

  SonarObstacle(long distance, unsigned long time) : Obstacle(time) {
    this->distance = distance;
  }

  bool isInRange(int range) {
    return (distance > 0 && distance <= range);
  }
};
