#pragma once

#include <AngleMovement.h>
#include "TimeAction.h"
#include "DelayedAction.h"

class ActionList {
	Action *current, *last = NULL;

	void moveToNext() {
		Action *next = current->getNext();
		delete current;
		current = next;
	}

	void add(Action* action) {
		if (isEmpty()) {
			current = action;
		} else {
			last->setNext(action);
		}
		last = action;
	}

public:
	void addAction(void (*f)(), unsigned long delay) {
		Action *action = new TimeAction(f, delay);
		add(action);
	}

	void addDelayedAction(void (*f)(), unsigned long delay) {
		Action *action = new DelayedAction(f, delay);
		add(action);
	}

	void addAngleMovement(void (*f)(), int angle) {
		Action *action = new AngleMovement(f, angle);
		add(action);
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
