#pragma once

#include "Obstacle.h"

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

  Arrangement findArrangement(long obstacleRange) {
    byte arr = NONE;
    if (frontLeft != NULL && frontLeft->isInRange(obstacleRange)) bitSet(arr, RIGHT_FRONT);
    if (frontRight != NULL && frontRight->isInRange(obstacleRange)) bitSet(arr, LEFT_FRONT);
    return static_cast<Arrangement>(arr);
  }
};
