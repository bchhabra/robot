#pragma once

class Action {
	void (*action)();
	unsigned long delay = 0;
	unsigned long startTime = 0;
	Action* next = NULL;

public:
	Action(void (*f)(), unsigned long delay) {
		action = f;
		this->delay = delay;
	}

	void playAction() {
		startTime = millis();
		action();
	}

	bool isFinished() {
		return ((delay == 0) || (millis() - startTime) >= delay);
	}

	bool isStarted() {
		return startTime > 0;
	}

	void setNext(Action* next) {
		this->next = next;
	}

	Action* getNext() {
		return next;
	}
};
