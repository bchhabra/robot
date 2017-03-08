#pragma once

#include "Wheel.h"

#define LEFT_FORWARD 5
#define LEFT_BACKWARD 8
#define RIGHT_FORWARD 7
#define RIGHT_BACKWARD 6

#define DELAY_TURN 160
Wheel leftWheel(LEFT_BACKWARD, LEFT_FORWARD, 9);
Wheel rightWheel(RIGHT_BACKWARD, RIGHT_FORWARD, 3);

enum Direction {
	none, forward, backward
} direction = none;

class Wheels {
	Wheel* left;
	Wheel* right;

	void delayAndStop(unsigned long delayTurn) {
		if (delayTurn != 0) {
			delay(delayTurn);
			doStop();
		}
	}

public:
	Wheels(Wheel* left, Wheel* right) {
		this->left = left;
		this->right = right;
	}

	void goForward(unsigned long delayTurn = 0) {
		Serial.println("go forward");
		left->forward();
		right->forward();
		delayAndStop(delayTurn);
	}

	void goBackward(unsigned long delayTurn = 0) {
		Serial.println("go backward");
		left->backward();
		right->backward();
		delayAndStop(delayTurn);
	}
	void goBackwardLeft(unsigned long delayTurn = 0) {
			Serial.println("go backward");
			/*
			 * 	left->backward(speed x);
			right->backward(speed x+y);
			delayAndStop(delayTurn);
			 *
			 */

		}
	void doStop() {
		Serial.println("do stop");
		left->stop();
		right->stop();
	}

	void goLeft(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("go left");
		left->stop();
		right->forward();
		delayAndStop(delayTurn);
	}

	void turnLeft(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("turn left");
		left->backward();
		right->forward();
		delayAndStop(delayTurn);
	}

	void moveAntiCockWise(unsigned long delayTurn = DELAY_TURN) {
			Serial.println("moving anti clock wise");
			/*
			 *
			left->forward(speed x);
			right->forward(speed x+y);
			delayAndStop(delayTurn);

			*/
	}
	void moveCockWise(unsigned long delayTurn = DELAY_TURN) {
			Serial.println("moving clock wise");
			/*
			 *
			left->forward(speed x+y);
			right->forward(speed x);
			delayAndStop(delayTurn);

			*/
	}

	void goRight(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("go right");
		left->forward();
		right->stop();
		delayAndStop(delayTurn);
	}

	void turnRight(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("turn right");
		left->forward();
		right->backward();
		delayAndStop(delayTurn);
	}

	void goLeftBack(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("go left back");
		left->stop();
		right->backward();
		delayAndStop(delayTurn);
	}

	void goRightBack(unsigned long delayTurn = DELAY_TURN) {
		Serial.println("go right back");
		left->backward();
		right->stop();
		delayAndStop(delayTurn);
	}

} w(&leftWheel, &rightWheel);
