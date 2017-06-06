#pragma once

#include "Wheel.h"
#include "SerialPrinter.h"

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

	void printInfo(const char* message) {
//		serial.println(message);
	}

public:
	Wheels(Wheel* left, Wheel* right) {
		this->left = left;
		this->right = right;
	}

	void goForward(unsigned long delayTurn = 0) {
		printInfo("go forward");
		left->forward();
		right->forward();
		delayAndStop(delayTurn);
	}

	void goBackward(unsigned long delayTurn = 0) {
		printInfo("go backward");
		left->backward();
		right->backward();
		delayAndStop(delayTurn);
	}
	
	void doStop() {
		printInfo("do stop");
		left->stop();
		right->stop();
	}

	void goLeft(unsigned long delayTurn = DELAY_TURN) {
		printInfo("go left");
		left->stop();
		right->forward();
		delayAndStop(delayTurn);
	}

	void turnLeft(unsigned long delayTurn = DELAY_TURN) {
		printInfo("turn left");
		left->backward();
		right->forward();
		delayAndStop(delayTurn);
	}

	void moveAntiClockWise() {
		printInfo("moving anti clock wise");
		left->forward();
		right->forward();
		delay(50);
		left->stop();
		delay(100);
		right->stop();
	}

	void moveClockWise() {
		printInfo("moving clock wise");
		left->forward();
		right->forward();
		delay(500);
		right->stop();
		delay(500);
		left->stop();
	}

	void goRight(unsigned long delayTurn = DELAY_TURN) {
		printInfo("go right");
		left->forward();
		right->stop();
		delayAndStop(delayTurn);
	}

	void turnRight(unsigned long delayTurn = DELAY_TURN) {
		printInfo("turn right");
		left->forward();
		right->backward();
		delayAndStop(delayTurn);
	}

	void goLeftBack(unsigned long delayTurn = DELAY_TURN) {
		printInfo("go left back");
		left->stop();
		right->backward();
		delayAndStop(delayTurn);
	}

	void goRightBack(unsigned long delayTurn = DELAY_TURN) {
		printInfo("go right back");
		left->backward();
		right->stop();
		delayAndStop(delayTurn);
	}

} w(&leftWheel, &rightWheel);
