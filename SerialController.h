#pragma once

#include "Controller.h"
#include "W.h"
#include "ActionList.h"

class SerialController: public Controller {

	Command getReceivedCommand() {
		String value = Serial.readStringUntil('\n');
		if (value == "f")
			return FORWARD;
		if (value == "b")
			return BACKWARD;
		if (value == "s")
			return STOP;
		if (value == "l")
			return LEFT;
		if (value == "r")
			return RIGHT;
		if (value == "lb")
			return LEFT_BACK;
		if (value == "rb")
			return RIGHT_BACK;
	}

public:
	void checkController() {
		if (Serial.available()) {
			actionList.removeAll();
			Command cmd = getReceivedCommand();
			switch (cmd) {
			case FORWARD:
				actionList.addAction(W::goForward, 0);
				break;
			case BACKWARD:
				actionList.addAction(W::goBackward, 0);
				break;
			case STOP:
				actionList.addAction(W::doStop, 0);
				break;
			case LEFT:
				actionList.addAction(W::goLeft, 0);
				break;
			case RIGHT:
				actionList.addAction(W::goRight, 0);
				break;
			case LEFT_BACK:
				actionList.addAction(W::goLeftBack, 0);
				break;
			case RIGHT_BACK:
				actionList.addAction(W::goRightBack, 0);
				break;
			}
		}
	}
};
