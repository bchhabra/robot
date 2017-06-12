#pragma once

#include <Arduino.h>
#include "Strategy.h"

class WifiStrategy: public Strategy {

public:
	void init() {
	}

	void run() {
	}

	void obstacleFound() {
		serial.println("obstacle found");
	}

} wifiStrategy;
