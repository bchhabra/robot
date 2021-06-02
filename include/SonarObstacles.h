#pragma once

#include "Obstacle.h"

#define OBSTACLE_RANGE 15

class SonarObstacles {
  Obstacle* frontLeft;
  Obstacle* frontRight;

public:
  enum Arrangement {
    NONE = 0,
    RIGHT_FRONT = 1,
    LEFT_FRONT = 2,
    BOTH_FRONT = 3
  } arrangement;

  SonarObstacles() {}

  SonarObstacles(Obstacle* frontLeft, Obstacle* frontRight) {
    this->frontLeft = frontLeft;
    this->frontRight = frontRight;
  }

  ~SonarObstacles() {
    delete frontLeft;
    delete frontRight;
  }

  Obstacle* getFrontLeft() {
    return frontLeft;
  }

  Obstacle* getFrontRight() {
    return frontRight;
  }

  Arrangement getClosest() {
    long diff = frontLeft->getDistance() - frontRight->getDistance();
    return diff > 0 ? RIGHT_FRONT : LEFT_FRONT;
  }

  bool isEmpty() {
    return (frontLeft == NULL) && (frontRight == NULL);
  }

  Arrangement findArrangement() {
    byte arr = NONE;
    if (frontLeft != NULL && frontLeft->isInRange(OBSTACLE_RANGE)) bitSet(arr, RIGHT_FRONT);
    if (frontRight != NULL && frontRight->isInRange(OBSTACLE_RANGE)) bitSet(arr, LEFT_FRONT);
    return static_cast<Arrangement>(arr);
  }
};
