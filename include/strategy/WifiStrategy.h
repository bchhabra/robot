#pragma once

#include "Strategy.h"

class WifiStrategy: public Strategy {

public:
	void init() {
	}

	void run() {
		if (actionList.isEmpty()) {
			Wheels::doStop();
		}
	}

	void obstacleFound(Obstacle* obstacle) {
//		actionList.removeAll();
//		actionList.addAction(Wheels::goBackward, 100);
	}

} wifiStrategy;
