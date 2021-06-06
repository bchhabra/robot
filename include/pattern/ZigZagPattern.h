#pragma once

#include <Arduino.h>
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
		actionList.addTimedAction(W::goForward, 0);
	}

	void obstacleFound(unsigned long interruptTime) {
		serial.println("Obstacle - ZigZag Pattern");
		interruptCounter++;

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - ZigZag Pattern with in 1 sec");
			actionList.addTimedAction(W::goBackward, 1500);
			actionList.addTimedAction(W::turnRight, 700);
		}
		if (interruptCounter % 2 == 0) {
			serial.println("Obstacle - ZigZag Pattern Even");
			actionList.addTimedAction(W::goBackward, 700);
			actionList.addTimedAction(W::turnRight, 1100);
			actionList.addTimedAction(W::goForward, 1100);
			actionList.addTimedAction(W::turnRight, 1100);
		} else {
			serial.println("Obstacle - ZigZag Pattern Odd");
			actionList.addTimedAction(W::goBackward, 700);
			actionList.addTimedAction(W::turnLeft, 1100);
			actionList.addTimedAction(W::goForward, 1100);
			actionList.addTimedAction(W::turnLeft, 1100);

		}

		lastInterruptTime = interruptTime;

	}

};

