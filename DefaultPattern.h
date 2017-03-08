#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class DefaultPattern: public Pattern {

/*
 * Will go always forward and on obstacle 90 left and next obstacle 90 right
 *
 */
	time_t startTime=time(NULL);
	time_t interruptTime=time(NULL);
	time_t lastinterruptTime;

public:
	void run() {
		w.goForward();

	}
	void obstacleFound() {
		interruptTime=time(NULL);
		double timediffernce = difftime(interruptTime, lastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}else{
			w.turnRight(2000); // To Be check and adjust 40 degress
		}

		lastinterruptTime=interruptTime;
	}



};
