#pragma once

#include <Arduino.h>
#include "Pattern.h"

class StopPattern: public Pattern {

public:
	StopPattern(const char* name) :
			Pattern(name) {
	}

	void run() {
		W::doStop();

	}

	void obstacleFound() {

	}

};
