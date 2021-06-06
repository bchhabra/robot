#pragma once

class Action {
	bool started = false;

public:
	Action* next = NULL;
	void (*parallel)() = NULL;

	Action() {}
	virtual ~Action(){}
	virtual bool isFinished() = 0;

	virtual void playAction() {
		started = true;
		if (parallel != NULL) parallel();
	}

	virtual bool isStarted() {
		return started;
	}
};
