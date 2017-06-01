#pragma once

class Action {
	void (*action)();
	unsigned long delay = 0;
	unsigned long startTime = 0;

public:
	Action(void (*f)(), unsigned long delay) {
		action = f;
		this->delay = delay;
	}

	void playAction() {
		startTime = millis();
		action();
	}

	bool shouldStop() {
		return ((millis() - startTime) >= delay);
	}

	bool isStarted() {
		return startTime > 0;
	}
};

