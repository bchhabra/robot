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
		actionList.addAction(W::goForward, 0);

	}

	void obstacleFound() {
		serial.println("Obstacle - ZigZag Pattern");
		unsigned long interruptTime = millis();
		interruptCounter++;

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - ZigZag Pattern with in 1 sec");
			actionList.addAction(W::goBackward, 1500);
			actionList.addAction(W::turnRight, 700);

		}
		if (interruptCounter % 2 == 0) {
			serial.println("Obstacle - ZigZag Pattern Even");
			actionList.addAction(W::goBackward, 700);
			actionList.addAction(W::turnRight, 1100);
			actionList.addAction(W::goForward, 1100);
			actionList.addAction(W::turnRight, 1100);
		} else {
			serial.println("Obstacle - ZigZag Pattern Odd");
			actionList.addAction(W::goBackward, 700);
			actionList.addAction(W::turnLeft, 1100);
			actionList.addAction(W::goForward, 1100);
			actionList.addAction(W::turnLeft, 1100);

		}

		lastInterruptTime = interruptTime;

	}

};

