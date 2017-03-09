#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

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

	time_t cPatternInterruptTime=time(NULL);
	time_t cPatternLastinterruptTime;

public:
	void run() {
		w.moveAntiCockWise();

	}
	void obstacleFound() {
		cPatternInterruptTime=time(NULL);
		double timediffernce = difftime(cPatternInterruptTime, cPatternLastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}else{
			w.turnLeft(2000); // To Be check and adjust 40 degress
		}

		cPatternLastinterruptTime=cPatternInterruptTime;
		run();
	}



};
