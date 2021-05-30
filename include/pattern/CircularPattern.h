#pragma once

#include <Arduino.h>
#include "Pattern.h"

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
	unsigned long fts = 10;
	unsigned long lts = 990;
	unsigned long factor = 75;
	unsigned long time_ts = 0;
	unsigned long runCounter = 0;
	unsigned long interruptCounter = 0;
	unsigned long lastRunTime = millis();
	unsigned long lastInterruptTime = millis();

public:
	CircularPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		runCounter++;
		unsigned long runTime = millis();
		time_ts = runTime - lastRunTime;
		String message = "time :: ";
		message.concat(time_ts);
//		serial.println(message.c_str());

		String message2 = "Counter :: ";
		message2.concat(runCounter);
//		serial.println(message2.c_str());

		if (runCounter % 10 == 0) {
			serial.println("C");
			fts = fts + factor;
			lts = lts - factor;
			if (lts < 0) {
				fts = 10;
				lts = 990;
			}
		}

		actionList.addAction(W::goForward, fts);
		actionList.addAction(W::goLeft, lts);
		lastRunTime = runTime;
	}

	void obstacleFound(unsigned long interruptTime) {
		interruptCounter++;
		serial.println("Obstacle - circular Pattern");
		actionList.addAction(W::goLeftBack, 200);
		actionList.addAction(W::goBackward, 150);
		actionList.addAction(W::goForward, 200);


		 if ((interruptTime - lastInterruptTime) < 1000) {
//			 serial.println("Obstacle - Circular Pattern with in 1 sec");
		 	 actionList.addAction(W::goLeftBack, 200);
		 	 actionList.addAction(W::goBackward, 150);
		 	 actionList.addAction(W::goForward, 200);
		 } else {
//		 serial.println("Obstacle - Circular Pattern else");
			 actionList.addAction(W::goLeftBack, 200);
			 actionList.addAction(W::goBackward, 200);
			 actionList.addAction(W::goForward, 100);
		 }

		lastInterruptTime = interruptTime;
	}

}
;
