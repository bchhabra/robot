#pragma once

#include "Obstacle.h"
byte const size = 4;

class Fifo {
  Obstacle* obst[size];
  int index = -1;

  void incIndex() {
    index = ++index % size;
  }

public:
  Fifo() {
    Obstacle obstacle = Obstacle();
    obst[0] = &obstacle;
  }

  void addObstacle(Obstacle* obstacle) {
    incIndex();
    obst[index] = obstacle;
  }

  Obstacle* getLastObstacle() {
    return obst[index];
  }

  Obstacle* getObstacle(int iterator) {
    return obst[((index - iterator) % size)];
  }
  
};

