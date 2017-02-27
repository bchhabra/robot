#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "Wheels.h"
#include "time.h"

#define PORT_CONTACTSENSORS 2

class RandomStrategy: public Strategy {

	int interruptCounter = 0;
	time_t startTime=time(NULL);
	time_t interruptTime=time(NULL);
	time_t lastinterruptTime;

public:
	void run(void (*f)()) {
		// implement logic
//		w.goForward();
		f();
	}
	void obstacleFound() {
		interruptTime=time(NULL);
		interruptCounter++;
		double timediffernce = difftime(interruptTime, lastinterruptTime);
		if(timediffernce<5){
			if(interruptCounter % 2 == 0){
						w.goBackward(100);
						w.turnLeft(1000);
					}else {
						w.goBackward(100);
						w.turnRight(1000);
					}
		}else{
			w.goBackward(2000);
		}

		lastinterruptTime=interruptTime;
	}
};
