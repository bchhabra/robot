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

		w.goForward(300);
		w.goLeft(300);

	}
	void obstacleFound() {
		unsigned long interruptTime = millis();

		if ((interruptTime - lastInterruptTime) < 1000) {
			Serial.println("Obstacle - Edge Pattern in 1 sec");
			w.goBackward(600);
			w.goLeftBack(300);

		} else {
			Serial.println("Obstacle - Edge Pattern");
			w.goBackward(500);
			w.goLeftBack(300);
		}

		lastInterruptTime = interruptTime;
		run();
	}
};
