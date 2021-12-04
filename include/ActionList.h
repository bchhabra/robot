#pragma once

#include "AngleMovement.h"
#include "TimedAction.h"
#include "component/Wheels.h"

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
		int mappedOffset = delay_to_deg(offset);
		if (f == Wheels::turnLeft) mappedOffset = -mappedOffset;
		return offset == 0 ? addTimedAction(f, offset) : add(new AngleMovement(f, mappedOffset));
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
