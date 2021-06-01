#pragma once

enum Direction {
  IRELEVANT,
  FRONT_LEFT,
  FRONT_RIGHT
};

class Obstacle {
  long distance = 0;
  unsigned long time = 0;
  Direction direction;

public:

  Obstacle(long distance, unsigned long time, Direction direction) {
    this->distance = distance;
    this->time = time;
    this->direction = direction;
  }

  long isInRange(int range) {
    return (distance > 0 && distance <= range) ? distance : 0;
  }

  unsigned long getTime() {
    return time;
  }

  long getDistance() {
    return distance;
  }

  Direction getDirection() {
    return direction;
  }
};
