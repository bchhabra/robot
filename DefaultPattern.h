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

		if ((interruptTime - lastInterruptTime) < 1000) {
			Serial.println("Obstacle - Default Pattern with in 2 sec");
			w.goBackward(700);
			w.goRight(500);

		} else {
			Serial.println("Obstacle - Default Pattern else");
			w.goBackward(300);
			w.goRight(500); // To Be check and adjust 40 degress
		}

		lastInterruptTime = interruptTime;
		run();
	}

};
