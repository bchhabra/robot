#pragma once

#include "Pattern.h"

class DefaultPattern: public Pattern {

	/*
	 * Will go always forward and on obstacle 90 left and next obstacle 90 right
	 *
	 */

	unsigned long lastInterruptTime = millis();

public:
	DefaultPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		actionList.addTimedAction(W::goForward, 0);
	}

	void obstacleFound(unsigned long interruptTime) {
//		serial.println("Obstacle - Default Pattern");

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - Default Pattern with in 2 sec");
			actionList.addTimedAction(W::goBackward, 700);
			actionList.addTimedAction(W::goRight, 700);
		} else {
			serial.println("Obstacle - Default Pattern else");
			actionList.addTimedAction(W::goBackward, 300);
			actionList.addTimedAction(W::goRight, 700);// To Be check and adjust 40 degress
		}

		lastInterruptTime = interruptTime;
	}

};
