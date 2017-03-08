#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "DefaultPattern.h"
#include "BoxPattern.h"
#include "ZigZagPattern.h"
#include "CircularPattern.h"
#include "EdgePattern.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class RandomStrategy: public Strategy {

	int interruptCounter = 0;
	time_t startTime = time(NULL);
	DefaultPattern dPattern;
	BoxPattern bPattern;
	ZigZagPattern zPattern;
	CircularPattern cPattern;
	EdgePattern ePattern;
	Pattern activePattern = dPattern;

public:
	void run(void (*f)()) {
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

		if (difftime(time(NULL), startTime) > 180) {
			// TODO FIXME if activePatterbn is default
			//Switch to differnt Pattern
			activePattern = cPattern;

		}
		activePattern.run();

	}
	void obstacleFound() {
		interruptCounter++;

		activePattern.obstacleFound();

		/* TODO FIXME below if case
		if (activePattern is cPattern){
					activePattern = ePattern;
					exit;
		}*/
		/*
		if( CircularPattern* cPattern = dynamic_cast< CircularPattern* >( &activePattern ) )
		{
			activePattern = ePattern;
							exit;
		}
		*/
		/*if (interruptCounter == 1) {

			activePattern = zpattern;

		}*/

	}

};
