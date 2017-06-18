#pragma once

#include "TimeAction.h"

class ActionList {
	Action *current, *last = NULL;

	void moveToNext() {
		Action *next = current->getNext();
		delete current;
		current = next;
	}

public:
	void addAction(void (*f)(), unsigned long delay) {
		Action *action = new TimeAction(f, delay);
		if (isEmpty()) {
			current = action;
		} else {
			last->setNext(action);
		}
		last = action;
	}

	void removeAll() {
		while (!isEmpty()) {
			moveToNext();
		}
	}

	bool isEmpty() {
		return current == NULL;
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

} actionList;
