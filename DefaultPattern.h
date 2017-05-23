#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"

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
	;

	void run() {
		w.goForward();

	}
	void obstacleFound() {
		Serial.println("Obstacle - Default Pattern");
		unsigned long interruptTime = millis();

		if ((interruptTime - lastInterruptTime) < 3000) {
			w.goBackward(3000);
			w.turnRight(1000);

		} else {
			w.turnRight(2000); // To Be check and adjust 40 degress
		}

		lastInterruptTime = interruptTime;
		run();
	}

};
