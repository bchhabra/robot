#include "Wheel.h"

class Wheels {
  Wheel* left;
  Wheel* right;
  int delayTurn;

public:
  Wheels(Wheel* left, Wheel* right, int delayTurn) {
    this->left = left;
    this->right = right;
    this->delayTurn = delayTurn;
  }

  void goForward() {
    left->forward();
    right->forward();
  }
  
  void goBackward() {
    left->backward();
    right->backward();
  }
  
  void doStop() {
    left->stop();
    right->stop();
  }

  void goLeft() {
    left->stop();
    right->forward();
    delay(delayTurn);
  }

  void turnLeft() {
    left->backward();
    right->forward();
    delay(delayTurn);
  }

  void goRight() {
    left->forward();
    right->stop();
    delay(delayTurn);
  }

  void turnRight() {
    left->forward();
    right->backward();
    delay(delayTurn);
  }

  void goLeftBack() {
    left->stop();
    right->backward();
    delay(delayTurn);
  }
  
  void goRightBack() {
    left->backward();
    right->stop();
    delay(delayTurn);
  }
  
};

