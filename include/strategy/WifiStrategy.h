#pragma once

#include <Arduino.h>
#include "Strategy.h"

class WifiStrategy: public Strategy {

public:
	void init() {
	}

	void run() {
		if (actionList.isEmpty()) {
			W::doStop();
		}
	}

	void obstacleFound(unsigned long interruptTime) {
//		actionList.removeAll();
//		actionList.addAction(W::goBackward, 100);
	}

} wifiStrategy;
