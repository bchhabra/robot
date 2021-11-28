#pragma once

#include "AngleMovement.h"
#include "TimedAction.h"

class ActionList {
	Action *current, *last = nullptr;

	void moveToNext() {
		Action *next = current->next;
		delete current;
		current = next;
	}

public:
	Action& add(Action* action) {
		if (isEmpty()) {
			current = action;
		} else {
			last->next = action;
		}
		last = action;
		return *action;
	}

	Action& addTimedAction(void (*f)(), unsigned long delay) {
		return add(new TimedAction(f, delay));
	}

	Action& addAngleMovement(void (*f)(), int angle) {
		return add(new AngleMovement(f, angle));
	}

	void removeAll() {
		while (!isEmpty()) {
			moveToNext();
		}
	}

	bool isEmpty() {
		return current == nullptr;
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
				playNextAction();
			}
		}
	}

} actionList, actionList2;
