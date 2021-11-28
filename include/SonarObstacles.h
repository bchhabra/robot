#pragma once

#include "SonarObstacle.h"

class SonarObstacles {

public:
  enum InRange {
    NONE        = 0b00,
    RIGHT_FRONT = 0b01,
    LEFT_FRONT  = 0b10,
    BOTH_FRONT  = 0b11
  } inRange;

  SonarObstacle frontLeft;
  SonarObstacle frontRight;

  InRange getClosest() {
    long diff = frontLeft.distance - frontRight.distance;
    return diff > 0 ? RIGHT_FRONT : LEFT_FRONT;
  }

  InRange findInRange(long obstacleRange) {
    byte arr = NONE;
    if (frontRight.isInRange(obstacleRange)) bitSet(arr, 0);
    if (frontLeft.isInRange(obstacleRange)) bitSet(arr, 1);
    return static_cast<InRange>(arr);
  }
};
