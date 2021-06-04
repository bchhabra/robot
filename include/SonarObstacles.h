#pragma once

#include "Obstacle.h"

class SonarObstacles {

public:
  Obstacle* frontLeft;
  Obstacle* frontRight;

  enum InRange {
    NONE        = 0b00,
    RIGHT_FRONT = 0b01,
    LEFT_FRONT  = 0b10,
    BOTH_FRONT  = 0b11
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
    if (frontRight != NULL && frontRight->isInRange(obstacleRange)) bitSet(arr, 0);
    if (frontLeft != NULL && frontLeft->isInRange(obstacleRange)) bitSet(arr, 1);
    return static_cast<InRange>(arr);
  }
};
