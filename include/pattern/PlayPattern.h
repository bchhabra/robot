#pragma once

#include "Pattern.h"

class PlayPattern: public Pattern {

	/*
	 * Will go always forward and on obstacle 90 left and next obstacle 90 right
	 *
	 */

	unsigned long lastInterruptTime = millis();

public:
	PlayPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		actionList.addAction(W::goForward, 0);
	}

	void obstacleFound(unsigned long interruptTime) {
		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - Default Pattern with in 2 sec");
			actionList.addAction(W::goBackward, 200);
			actionList.addAction(W::goRight, 700);
		} else {
			serial.println("Obstacle - Default Pattern else");
			actionList.addAction(W::goBackward, 200);
			actionList.addAction(W::goLeft, 700);// To Be check and adjust 40 degress
		}

		lastInterruptTime = interruptTime;
	}

};
