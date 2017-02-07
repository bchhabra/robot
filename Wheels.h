#pragma once

#include "Wheel.h"

#define LEFT_FORWARD 5
#define LEFT_BACKWARD 8
#define RIGHT_FORWARD 7
#define RIGHT_BACKWARD 6

#define DELAY_TURN 160
Wheel leftWheel(LEFT_BACKWARD, LEFT_FORWARD, 9);
Wheel rightWheel(RIGHT_BACKWARD, RIGHT_FORWARD, 3);

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

} w(&leftWheel, &rightWheel, DELAY_TURN);
