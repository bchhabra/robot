#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "W.h"
#include "ActionList.h"

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

	void run() {
		actionList.addAction(new Action(W::goForward, 300));
		actionList.addAction(new Action(W::goLeft, 600));
	}

	void obstacleFound() {
		serial.println("Obstacle - circular Pattern");
		unsigned long interruptTime = millis();

		if ((interruptTime - lastInterruptTime) < 1000) {
			serial.println("Obstacle - Circular Pattern with in 1 sec");
			actionList.addAction(new Action(W::goBackward, 700));
			actionList.addAction(new Action(W::goRight, 700));
		} else {
			serial.println("Obstacle - Circular Pattern else");
			actionList.addAction(new Action(W::goBackward, 300));
			actionList.addAction(new Action(W::goRight, 700));
		}

		lastInterruptTime = interruptTime;
		run();
	}

};
