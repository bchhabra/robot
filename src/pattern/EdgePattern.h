#pragma once

#include <Arduino.h>
#include "Pattern.h"

class EdgePattern: public Pattern {

	unsigned long lastInterruptTime = millis();
	boolean isWall = false;
public:
	EdgePattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		/**
		 * This pattern should run for maximum 180 secs
		 *
		 */
		if(isWall){
			actionList.addAction(W::goLeft, 1000);
			actionList.addAction(W::goForward, 200);
		}else{
			actionList.addAction(W::goForward, 500);
			actionList.addAction(W::goLeft, 500);
		}
	}

	void obstacleFound() {
		/*
		 * if you hit the obstacle in 3 secs than consider you are following the wall
		 *
		 */

		unsigned long interruptTime = millis();
		if(interruptTime-lastInterruptTime < 3000){
			isWall=true;
		}

		actionList.addAction(W::goLeftBack, 500);
		actionList.addAction(W::goForward, 300);

		lastInterruptTime = interruptTime;
	}
};
