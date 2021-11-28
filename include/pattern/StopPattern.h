#pragma once

#include "Pattern.h"

class StopPattern: public Pattern {

public:
	StopPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		actionList.addTimedAction(W::doStop, 0);
	}

	void obstacleFound(unsigned long interruptTime) {

	}

};
