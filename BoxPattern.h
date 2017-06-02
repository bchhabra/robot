#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

class BoxPattern: public Pattern {

	/*
	 * Will go always forward and on obstacle 90
	 *
	 */

	unsigned long lastInterruptTime = millis();

public:
	BoxPattern(const char* name) :
			Pattern(name) {
	}
	;

	void run() {
		w.goForward();

	}
	void obstacleFound() {
		Serial.println("Obstacle - Box Pattern");
		unsigned long interruptTime = millis();

		if ((interruptTime - lastInterruptTime) < 1000) {
			Serial.println("Obstacle - Box Pattern with in 2 sec");
			w.goBackward(700);
			w.goRight(500);

		} else {
			Serial.println("Obstacle - Box Pattern else");
			w.goBackward(300);
			w.turnRight(500); // To Be check and adjust 90 degress
		}

		lastInterruptTime = interruptTime;
		run();
	}

};
