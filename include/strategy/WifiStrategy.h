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

	void obstacleFound(Obstacle* obstacle) {
//		actionList.removeAll();
//		actionList.addAction(W::goBackward, 100);
	}

} wifiStrategy;
