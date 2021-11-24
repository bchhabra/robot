#pragma once

#if SOUND

#include <Arduino.h>
#include "Action.h"
#include "Pins.h"

class ToneAction : public Action {
	int delay = 0;
	unsigned long finishTime = UINT32_MAX;
	int note = 0;
	int noteDuration = 0;

public:
	ToneAction(int note, int noteDuration) : Action(nullptr) {
		this->note = note;
		this->noteDuration = noteDuration*1.3;
		this->delay = noteDuration*1.6;
	}

	~ToneAction() {
		noTone(PIEZZO_PIN);
	}

	void playAction() override {
		finishTime = millis() + delay;
		tone(PIEZZO_PIN, note, noteDuration);
		Action::playAction();
	}

	bool isFinished() override {
		return millis() >= finishTime;
	}
};

#endif