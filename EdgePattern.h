#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

class EdgePattern: public Pattern {

	/*
	 * Will go always circular anti clock wise and on obstacle should change the pattern to edge pattern
	 *
	 */
	time_t ePatternStartTime = time(NULL);
	time_t ePatternInterruptTime = time(NULL);
	time_t ePatternLastinterruptTime;
	int interruptCounter = 0;

public:
	void run() {
		/**
		 * This pattern should run for maximum 180 secs
		 *
		 */
		if (difftime(time(NULL), ePatternStartTime) < 180) {

			if (interruptCounter == 0) {
				w.goForward();
			}
			w.goForward();
			w.turnLeft();
		}

	}
	void obstacleFound() {
		interruptCounter++;
		ePatternInterruptTime = time(NULL);
		double timediffernce = difftime(ePatternInterruptTime,
				ePatternLastinterruptTime);
		if (timediffernce < 3) {
			w.goBackward(3000);
			w.turnRight(1000);

		} else {
			w.goBackwardLeft(2000);
		}
		ePatternLastinterruptTime = ePatternInterruptTime;
		run();
	}

};
