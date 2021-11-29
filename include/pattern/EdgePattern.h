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
			actionList.addTimedAction(Wheels::goLeft, 1000);
			actionList.addTimedAction(Wheels::goForward, 200);
		}else{
			actionList.addTimedAction(Wheels::goForward, 500);
			actionList.addTimedAction(Wheels::goLeft, 500);
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

		actionList.addTimedAction(Wheels::goLeftBack, 500);
		actionList.addTimedAction(Wheels::goForward, 300);

		lastInterruptTime = interruptTime;
	}
};
