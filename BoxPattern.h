#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

class BoxPattern: public Pattern {

/*
 * Will go always forward and on obstacle 90
 *
 */

	time_t bPatternInterruptTime=time(NULL);
	time_t bPatternLastinterruptTime;

public:
	void run() {
		w.goForward(10000);

	}
	void obstacleFound() {
		bPatternInterruptTime=time(NULL);
		double timediffernce = difftime(bPatternInterruptTime, bPatternLastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}else{
			w.turnRight(3500); // To Be check and adjust as 90
		}

		bPatternLastinterruptTime=bPatternInterruptTime;
	}



};
