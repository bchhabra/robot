#include "Obstacle.h"
byte const size = 4;

class Fifo {
  Obstacle* obst[size];
  int index = 0;

  void incIndex() {
    index = ++index % size;
  }

public:
  void addObstacle(Obstacle* obst) {
    incIndex();
    obst[index] = *obst;
  }

  Obstacle* getLastObstacle() {
    return obst[index];
  }

  Obstacle* getObstacle(int iterator) {
    return obst[((index - iterator) % size)];
  }
  
};

