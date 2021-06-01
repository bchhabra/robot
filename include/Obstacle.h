#pragma once

class Obstacle {
  long distance = 0;
  unsigned long time = 0;

public:
  Obstacle(long distance, unsigned long time ) {
    this->distance = distance;
    this->time = time;
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
};
