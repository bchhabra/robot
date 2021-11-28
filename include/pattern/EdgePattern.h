#pragma once

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
			actionList.addTimedAction(W::goLeft, 1000);
			actionList.addTimedAction(W::goForward, 200);
		}else{
			actionList.addTimedAction(W::goForward, 500);
			actionList.addTimedAction(W::goLeft, 500);
		}
	}

	void obstacleFound(unsigned long interruptTime) {
		/*
		 * if you hit the obstacle in 3 secs than consider you are following the wall
		 *
		 */

		if(interruptTime-lastInterruptTime < 3000){
			isWall=true;
		}

		actionList.addTimedAction(W::goLeftBack, 500);
		actionList.addTimedAction(W::goForward, 300);

		lastInterruptTime = interruptTime;
	}
};
