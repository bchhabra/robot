#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

class DefaultPattern: public Pattern {

/*
 * Will go always forward and on obstacle 90 left and next obstacle 90 right
 *
 */

	time_t dPatternInterruptTime=time(NULL);
	time_t dPatternLastinterruptTime;

public:
	void run() {
		w.goForward();

	}
	void obstacleFound() {
		dPatternInterruptTime=time(NULL);
		double timediffernce = difftime(dPatternInterruptTime, dPatternLastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}else{
			w.turnRight(2000); // To Be check and adjust 40 degress
		}

		dPatternLastinterruptTime=dPatternInterruptTime;
		run();
	}



};
