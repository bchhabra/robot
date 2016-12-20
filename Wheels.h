#include "Wheel.h"

class Wheels {
  Wheel* left;
  Wheel* right;
  int delayTurn;

public:
  Wheels(Wheel* left, Wheel* right, int delayTurn, int speed) {
    this->left = left;
    this->right = right;
    this->delayTurn = delayTurn;
    right->setSpeed(speed);
    left->setSpeed(speed);
  }

  void goForward() {
    left->forward();
    right->forward();
    Serial.println("go forward");
  }
  
  void goBackward() {
    left->backward();
    right->backward();
    Serial.println("go bacward");
  }
  
  void doStop() {
    left->stop();
    right->stop();
    Serial.println("do stop");
  }

  void goLeft() {
    left->stop();
    right->forward();
    delay(delayTurn);
    Serial.println("go left");
  }

  void turnLeft() {
    left->backward();
    right->forward();
    delay(delayTurn);
    Serial.println("turn left");
  }

  void goRight() {
    left->forward();
    right->stop();
    delay(delayTurn);
    Serial.println("go right");
  }

  void turnRight() {
    left->forward();
    right->backward();
    delay(delayTurn);
    Serial.println("turn right");
  }

  void goLeftBack() {
    left->stop();
    right->backward();
    delay(delayTurn);
    Serial.println("go left back");
  }
  
  void goRightBack() {
    left->backward();
    right->stop();
    delay(delayTurn);
    Serial.println("go right back");
  }
  
};

