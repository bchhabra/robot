#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "Wheels.h"

#define PORT_CONTACTSENSORS 2

class RandomStrategy: public Strategy {
public:
	void run(void (*f)()) {
		// implement logic
		w.goForward(100);
	}
	void obstacleFound(int interruptCounter, double timediffernce) {
		if(timediffernce<0.0005){
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


	}
};
