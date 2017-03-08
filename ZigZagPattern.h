#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class ZigZagPattern: public Pattern {

/*
 * Will go always forward and on obstacle 90 left and next obstacle 90 right
 *
 */
	time_t startTime=time(NULL);
	time_t interruptTime=time(NULL);
	time_t lastinterruptTime;
	int interruptCounter = 0;


public:
	void run() {
		w.goForward();

	}
	void obstacleFound() {
		interruptCounter++;
		interruptTime=time(NULL);
		double timediffernce = difftime(interruptTime, lastinterruptTime);
		if(timediffernce<3){
						w.goBackward(3000);
						w.turnRight(1000);

		}
		if(interruptCounter % 2 == 0){
					w.goBackward(100);
					w.turnLeft(3500);
					w.goForward(1000);
					w.turnLeft(3500);
		}else {
					w.goBackward(100);
					w.turnRight(3500); // To Be check and adjust as 90
					w.goForward(1000);
					w.turnRight(3500);
		}
		lastinterruptTime=interruptTime;
	}



};



