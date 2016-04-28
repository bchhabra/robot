#include "Wheel.h"

class Wheels {
  Wheel* left;
  Wheel* right;
  int delayTurn = 200;

public:
  Wheels(Wheel* left, Wheel* right) {
    this->left = left;
    this->right = right;
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

  void goRight() {
    left->forward();
    right->stop();
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

