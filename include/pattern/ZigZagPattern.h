#pragma once

#include "Pattern.h"

class ZigZagPattern: public Pattern {

	/*
	 * Will go always forward and on obstacle 90 left and next obstacle 90 right
	 *
	 */
	unsigned long lastInterruptTime = millis();
	int interruptCounter = 0;

public:
	ZigZagPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		actionList.addTimedAction(Wheels::goForward, 0);
	}

	void obstacleFound(unsigned long interruptTime) {
		serial.println("Obstacle - ZigZag Pattern");
		interruptCounter++;

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - ZigZag Pattern with in 1 sec");
			actionList.addTimedAction(Wheels::goBackward, 1500);
			actionList.addTimedAction(Wheels::turnRight, 700);
		}
		if (interruptCounter % 2 == 0) {
			serial.println("Obstacle - ZigZag Pattern Even");
			actionList.addTimedAction(Wheels::goBackward, 700);
			actionList.addTimedAction(Wheels::turnRight, 1100);
			actionList.addTimedAction(Wheels::goForward, 1100);
			actionList.addTimedAction(Wheels::turnRight, 1100);
		} else {
			serial.println("Obstacle - ZigZag Pattern Odd");
			actionList.addTimedAction(Wheels::goBackward, 700);
			actionList.addTimedAction(Wheels::turnLeft, 1100);
			actionList.addTimedAction(Wheels::goForward, 1100);
			actionList.addTimedAction(Wheels::turnLeft, 1100);

		}

		lastInterruptTime = interruptTime;

	}

};

