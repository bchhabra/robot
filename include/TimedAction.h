#pragma once

#include <Arduino.h>
#include "DelegateAction.h"

class TimedAction : public DelegateAction {
	unsigned long delay = 0;
	unsigned long finishTime = UINT32_MAX;

public:
	TimedAction(void (*f)(), unsigned long delay) : DelegateAction(f) {
		this->delay = delay;
	}

	void playAction() {
		finishTime = millis() + delay;
		DelegateAction::playAction();
	}

	bool isFinished() {
		// a delay of 0 means the action never finishes unless some obstacle is found
		return ((delay > 0) && (millis() >= finishTime));
	}

};
