#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"

class CircularPattern: public Pattern {

	/*
	 * Will go always circular anti clock wise and on obstacle should change the pattern to edge pattern
	 *
	 */
	/*
	 * We need new methods in Wheel class which can support delay on each wheel.
	 * Currently we have a delay on direction.
	 *
	 * This is needed for circular and edge pattern.
	 * lets say for circular
	 * left wheel forward for 500 ms and right wheel forward for 700 ms
	 * or left wheel speed x forward direction right wheel speed x+y forward direction
	 *
	 */

	unsigned long lastInterruptTime = millis();

public:
	CircularPattern(const char* name) :
			Pattern(name) {
	}
	;

	void run() {
		w.moveAntiCockWise();

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
