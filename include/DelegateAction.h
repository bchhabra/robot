#pragma once

#include "Action.h"

class DelegateAction : public Action {
	void (*action)() = NULL;

public:
	DelegateAction(void (*f)()) {
		this->action = f;
	}

	~DelegateAction() {
	}

	void playAction() {
		if (action != NULL) action();
		Action::playAction();
	}
};
