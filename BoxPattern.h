#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class BoxPattern: public Pattern {

/*
 * Will go always forward and on obstacle 90
 *
 */
	time_t startTime=time(NULL);
	time_t interruptTime=time(NULL);
	time_t lastinterruptTime;

public:
	void run() {
		w.goForward(10000);

	}
	void obstacleFound() {
		interruptTime=time(NULL);
		double timediffernce = difftime(interruptTime, lastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}else{
			w.turnRight(3500); // To Be check and adjust as 90
		}

		lastinterruptTime=interruptTime;
	}



};
