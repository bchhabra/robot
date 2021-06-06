#pragma once

#include <AngleMovement.h>
#include "TimedAction.h"

class ActionList {
	Action *current, *last = NULL;

	void moveToNext() {
		Action *next = current->next;
		delete current;
		current = next;
	}

public:
	void add(Action* action) {
		if (isEmpty()) {
			current = action;
		} else {
			last->next = action;
		}
		last = action;
	}

	Action* addTimedAction(void (*f)(), unsigned long delay) {
		Action *action = new TimedAction(f, delay);
		add(action);
		return action;
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
				playNextAction();
			}
		}
	}

} actionList, actionList2;
