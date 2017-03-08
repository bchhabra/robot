#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "DefaultPattern.h"
#include "BoxPattern.h"
#include "ZigZagPattern.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class RandomStrategy: public Strategy {

	int interruptCounter = 0;
	time_t startTime = time(NULL);
	DefaultPattern dpattern;
	BoxPattern bpattern;
	ZigZagPattern zpattern;
	Pattern activePattern = dpattern;

public:
	void run(void (*f)()) {
		/* go straight  (initial 10 sec)
		 * on obstacle turn right 40 degree and than forward  (uptp 3 mins)
		 * circular mode (upto next obstacle)
		 * then it goes to edge mode (for next 3 mins)
		 * loop restart
		 */
		// implement logic
		if (difftime(time(NULL), startTime) > 10) {
			//Switch to differnt Pattern
			activePattern = zpattern;

		}
		activePattern.run();

	}
	void obstacleFound() {
		interruptCounter++;
		activePattern.obstacleFound();
		/*if (interruptCounter == 1) {

			activePattern = zpattern;

		}*/

	}

};
