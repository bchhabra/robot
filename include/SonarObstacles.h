#pragma once

#include "SonarObstacle.h"

class SonarObstacles {

public:
  SonarObstacle* frontLeft;
  SonarObstacle* frontRight;

  enum InRange {
    NONE        = 0b00,
    RIGHT_FRONT = 0b01,
    LEFT_FRONT  = 0b10,
    BOTH_FRONT  = 0b11
  } inRange;

  SonarObstacles() {}

  SonarObstacles(SonarObstacle* frontLeft, SonarObstacle* frontRight) {
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
    long diff = frontLeft->distance - frontRight->distance;
    return diff > 0 ? RIGHT_FRONT : LEFT_FRONT;
  }

  InRange findInRange(long obstacleRange) {
    byte arr = NONE;
    if (frontRight != nullptr && frontRight->isInRange(obstacleRange)) bitSet(arr, 0);
    if (frontLeft != nullptr && frontLeft->isInRange(obstacleRange)) bitSet(arr, 1);
    return static_cast<InRange>(arr);
  }
};
