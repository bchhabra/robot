#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

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
	;

	void run() {
		actionList.addAction(new Action(W::goForward, 0));

	}
	void obstacleFound() {
		Serial.println("Obstacle - ZigZag Pattern");
		unsigned long interruptTime = millis();
		interruptCounter++;

		if ((interruptTime - lastInterruptTime) < 1000) {
			Serial.println("Obstacle - ZigZag Pattern with in 1 sec");
			actionList.addAction(new Action(W::goBackward, 1500));
			actionList.addAction(new Action(W::turnRight, 700));

		}
		if (interruptCounter % 2 == 0) {
			Serial.println("Obstacle - ZigZag Pattern Even");
			actionList.addAction(new Action(W::goBackward, 700));
			actionList.addAction(new Action(W::turnRight, 1100));
			actionList.addAction(new Action(W::goForward, 1100));
			actionList.addAction(new Action(W::turnRight, 1100));
		} else {
			Serial.println("Obstacle - ZigZag Pattern Odd");
			actionList.addAction(new Action(W::goBackward, 700));
			actionList.addAction(new Action(W::turnLeft, 1100));
			actionList.addAction(new Action(W::goForward, 1100));
			actionList.addAction(new Action(W::turnLeft, 1100));

		}

		lastInterruptTime = interruptTime;
		run();

	}

};

