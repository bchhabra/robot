#pragma once

#include <Arduino.h>
#include "Pattern.h"
#include "Wheels.h"

class StopPattern: public Pattern {

public:
	StopPattern(const char* name) :
			Pattern(name) {
	}
	;

	void run() {
		w.doStop();

	}
	void obstacleFound() {

	}

};
