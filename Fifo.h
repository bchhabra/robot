#pragma once

#include "Obstacle.h"

class Fifo {
	int size;
	Obstacle** obst;
	int index = -1;

  void incIndex() {
    index = ++index % size;
  }

public:
  Fifo(int size) {
	this->size = size;
	obst = new Obstacle*[size];
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

