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
		w.goForward();

	}
	void obstacleFound() {
		Serial.println("Obstacle - ZigZag Pattern");
		unsigned long interruptTime = millis();
		interruptCounter++;

		if ((interruptTime - lastInterruptTime) < 1000) {
			Serial.println("Obstacle - ZigZag Pattern with in 1 sec");
			w.goBackward(1200);
			w.turnRight(500);

		}
		if (interruptCounter % 2 == 0) {
			Serial.println("Obstacle - ZigZag Pattern Even");
			w.goBackward(700);
			w.turnRight(1100); // To Be check and adjust 90 degress
			w.goForward(1200);
			w.turnRight(1100); // To Be check and adjust 90 degress
		} else {
			Serial.println("Obstacle - ZigZag Pattern Odd");
			w.goBackward(700);
			w.turnLeft(1100); // To Be check and adjust 90 degress
			w.goForward(1200);
			w.turnLeft(1100); // To Be check and adjust 90 degress
		}

		lastInterruptTime = interruptTime;
		run();

	}

};

