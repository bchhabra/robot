#pragma once

#include <Arduino.h>
#include "Action.h"

class TimeAction : public Action {
	unsigned long delay = 0;
	unsigned long startTime = 0;

public:
	TimeAction(void (*f)(), unsigned long delay) : Action(f) {
		this->delay = delay;
	}

	void playAction() {
		startTime = millis();
		action();
	}

	bool isFinished() {
		// a delay of 0 means the action never finishes unless some obstacle is found
		return ((delay > 0) && (millis() - startTime) >= delay);
	}

	bool isStarted() {
		return startTime > 0;
	}
};
