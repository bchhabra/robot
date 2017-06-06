#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "W.h"
#include "ActionList.h"

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
		actionList.addAction(new Action(W::goForward, 0));
	}

	void obstacleFound() {
		serial.println("Obstacle - Default Pattern");
		unsigned long interruptTime = millis();

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - Default Pattern with in 2 sec");
			actionList.addAction(new Action(W::goBackward, 700));
			actionList.addAction(new Action(W::goRight, 700));

		} else {
			serial.println("Obstacle - Default Pattern else");
			actionList.addAction(new Action(W::goBackward, 300));
			actionList.addAction(new Action(W::goRight, 700));// To Be check and adjust 40 degress
		}

		lastInterruptTime = interruptTime;
		run();
	}

};
