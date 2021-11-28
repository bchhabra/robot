#pragma once

class Obstacle {

public:
  unsigned long time = 0;

  Obstacle() {
  }

  Obstacle(unsigned long time) {
    this->time = time;
  }
};
