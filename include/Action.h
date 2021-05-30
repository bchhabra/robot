#pragma once

#include <Arduino.h>

class Action {
protected:
	void (*action)();
	Action* next = NULL;

public:
	Action(void (*f)()) {
		action = f;
	}
	virtual ~Action(){}
	virtual void playAction() = 0;
	virtual bool isFinished() = 0;
	virtual bool isStarted() = 0;

	void setNext(Action* next) {
		this->next = next;
	}

	Action* getNext() {
		return next;
	}
};
