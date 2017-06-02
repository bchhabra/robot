#pragma once

#include "Action.h"

class ActionList {
	Action *current, *last = NULL;

	bool isEmpty() {
		return current == NULL;
	}

	void moveToNext() {
		Action* next = current->getNext();
		delete current;
		current = next;
	}

public:
	void addAction(Action* action) {
		if (isEmpty()) {
			current = action;
		} else {
			last->setNext(action);
		}
		last = action;
	}

	void empty() {
		while (!isEmpty()) {
			moveToNext();
		}
	}

	void playNextAction() {
		if (isEmpty()) {
			return;
		}

		if (!current->isStarted()) {
			current->playAction();
		} else {
			if (current->isFinished()) {
				moveToNext();
			}
		}
	}

	bool isLastActionFinished() {
		return isEmpty() || last->isFinished();
	}

} actionList;
