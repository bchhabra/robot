#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "pattern/DefaultPattern.h"
#include "pattern/ZigZagPattern.h"
#include "pattern/CircularPattern.h"
#include "pattern/EdgePattern.h"
#include "pattern/StopPattern.h"

class RandomStrategy: public Strategy {

	int interruptCounter = 0;
	unsigned long startTime = 0;
	DefaultPattern dPattern { "default" };
	ZigZagPattern zPattern { "zig-zag" };
	CircularPattern cPattern { "circular" };
	EdgePattern ePattern { "edge" };
	StopPattern sPattern { "stop" };

public:
	void init() {
		changePattern(&dPattern);
		startTime = millis();
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
*/

		if ((millis() - startTime) > 20000) {
			// TODO FIXME if activePatterbn is default
			//Switch to differnt Pattern
			changePattern(&cPattern);
			actionList.removeAll();
		}
		if ((millis() - startTime) > 60000) {
			// Stop Vaccum, Stop Wheels
			changePattern(&sPattern);
			actionList.removeAll();
		}

		if (actionList.isEmpty()) {
			activePattern->run();
		}
	}

	void obstacleFound() {
		interruptCounter++;

		W::doStop();
		actionList.removeAll();

		//serial.println("Obstacle Found Random Strategy");
		activePattern->obstacleFound();
	}

};
