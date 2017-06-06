#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "DefaultPattern.h"
#include "ZigZagPattern.h"
#include "CircularPattern.h"
#include "EdgePattern.h"
#include "StopPattern.h"

class RandomStrategy: public Strategy {

	int interruptCounter = 0;
	unsigned long startTime = millis();
	DefaultPattern dPattern { "default" };
	ZigZagPattern zPattern { "zig-zag" };
	CircularPattern cPattern { "circular" };
	EdgePattern ePattern { "edge" };
	StopPattern sPattern { "stop" };

public:
	void init() {
		changePattern(&dPattern);
	}

	void run() {
		/* go straight  (initial 10 sec)
		 * on obstacle turn right 40 degree and than forward  (uptp 3 mins)
		 * circular mode (upto next obstacle)
		 * then it goes to edge mode (for next 3 mins)
		 * loop restart
		 */
		/* // implement logic
		 * object should start with default pattern for 3 mins.
		 * goes into circular pattern till he get an obstacle.
		 * goes into edge pattern for 3 mins.
		 * Investigation on speed pin in needed.
		 *


		if ((millis() - startTime) > 60000) {
			// TODO FIXME if activePatterbn is default
			//Switch to differnt Pattern
			changePattern(&cPattern);
		}
		if ((millis() - startTime) > 60000) {
			// Stop Vaccum, Stop Wheels
			changePattern(&sPattern);
		} */
		activePattern->run();

	}
	void obstacleFound() {
		interruptCounter++;

		//serial.println("Obstacle Found Random Strategy");
		activePattern->obstacleFound();
	}

};
