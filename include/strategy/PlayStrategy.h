#pragma once

#include "Strategy.h"
#include "pattern/PlayPattern.h"

class PlayStrategy: public Strategy {

	PlayPattern pattern { "play" };
public:
	void init() {
		changePattern(&pattern);
	}

	void run() {
		if (actionList.isEmpty()) {
			activePattern->run();
		}
	}

	void obstacleFound(unsigned long interruptTime) {
		W::doStop();
		actionList.removeAll();

		activePattern->obstacleFound(interruptTime);
	}

} playStrategy;
