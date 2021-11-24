#pragma once

class Action {
	bool started = false;
	void (*action)() = nullptr;
	void (*parallel)() = nullptr;

public:
	Action* next = nullptr;

	virtual ~Action() {}
	virtual bool isFinished() = 0;

	Action(void (*f)()) {
		action = f;
	}

	virtual void playAction() {
		started = true;
		if (action != nullptr) action();
		if (parallel != nullptr) parallel();
	}

	void andInParallel(void (*f)()) {
		parallel = f;
	}

	virtual bool isStarted() {
		return started;
	}
};
