#pragma once

#include "Action.h"

class ActionController {
	int size = 10;
	Action** actions;
	int index = 0;
	int execIndex = 0;

	void incIndex() {
		index = ++index % size;
	}

	void incExecIndex() {
		execIndex = ++execIndex % size;
	}

	bool isLastAction() {
		return execIndex == index;
	}

public:
	ActionController(int size) {
		this->size = size;
		actions = new Action*[size];
	}

	void addAction(Action* action) {
		incIndex();
		actions[index] = action;
	}

	void playNextAction() {
		Action* currentAction = actions[execIndex];
		if (currentAction == NULL) {
			return;
		}

		if (!currentAction->isStarted()) {
			currentAction->playAction();
		} else {
			if (currentAction->shouldStop()) {
				if (isLastAction()) {
					currentAction->playAction();
				} else {
					incExecIndex();
					playNextAction();
				}
			}
		}
	}

} actionController { 100 };

