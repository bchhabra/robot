#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

class EdgePattern: public Pattern {

	unsigned long lastInterruptTime = millis();
public:
	EdgePattern(const char* name) :
			Pattern(name) {
	}
	;

	void run() {
		/**
		 * This pattern should run for maximum 180 secs
		 *
		 */

		actionList.addAction(new Action(W::goLeft, 1400));
		actionList.addAction(new Action(W::goForward, 500));
	}
	void obstacleFound() {
		unsigned long interruptTime = millis();
		serial.println("Obstacle - Edge Pattern");
		actionList.addAction(new Action(W::goLeftBack, 500));
		actionList.addAction(new Action(W::goForward, 300));
/*
		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - Edge Pattern in 1 sec");
			w.goBackward(600);
			w.goLeftBack(300);

		} else {
			serial.println("Obstacle - Edge Pattern");
			actionList.addAction(new Action(W::goLeftBack, 300));
			actionList.addAction(new Action(W::goForward, 300));
		}*/

		lastInterruptTime = interruptTime;
		run();
	}
};
