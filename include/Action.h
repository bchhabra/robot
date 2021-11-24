#pragma once

class Action {
	bool started = false;
	void (*action)() = NULL;
	void (*parallel)() = NULL;

public:
	Action* next = NULL;

	virtual ~Action() {}
	virtual bool isFinished() = 0;

	Action(void (*f)()) {
		action = f;
	}

	virtual void playAction() {
		started = true;
		if (action != NULL) action();
		if (parallel != NULL) parallel();
	}

	void andInParallel(void (*f)()) {
		parallel = f;
	}

	virtual bool isStarted() {
		return started;
	}
};
