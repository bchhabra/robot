#pragma once

#include "Obstacle.h"

class SonarObstacles {

public:
  Obstacle* frontLeft;
  Obstacle* frontRight;

  enum InRange {
    NONE = 0,
    RIGHT_FRONT = 1,
    LEFT_FRONT = 2,
    BOTH_FRONT = 3
  } inRange;

  SonarObstacles() {}

  SonarObstacles(Obstacle* frontLeft, Obstacle* frontRight) {
    this->frontLeft = frontLeft;
    this->frontRight = frontRight;
  }

  ~SonarObstacles() {
    deleteObstacles();
  }

  void deleteObstacles() {
    delete frontLeft;
    delete frontRight;
  }

  InRange getClosest() {
    long diff = frontLeft->getDistance() - frontRight->getDistance();
    return diff > 0 ? RIGHT_FRONT : LEFT_FRONT;
  }

  bool isEmpty() {
    return (frontLeft == NULL) && (frontRight == NULL);
  }

  InRange findInRange(long obstacleRange) {
    byte arr = NONE;
    if (frontRight != NULL && frontRight->isInRange(obstacleRange)) bitSet(arr, RIGHT_FRONT-1);
    if (frontLeft != NULL && frontLeft->isInRange(obstacleRange)) bitSet(arr, LEFT_FRONT-1);
    return static_cast<InRange>(arr);
  }
};
