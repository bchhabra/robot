#pragma once

#include "AngleMovement.h"
#include "TimedAction.h"

#define delay_to_deg(delay) (((unsigned long)delay)*360/4000)

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

	Action& addTurnAction(void (*f)(), unsigned long offset) {
#if IMU
		return offset == 0 ? addTimedAction(f, offset) : add(new AngleMovement(f, delay_to_deg(offset)));
#else
		return addTimedAction(f, offset);
#endif
	}

	Action& addTimedAction(void (*f)(), unsigned long delay) {
		return add(new TimedAction(f, delay));
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
