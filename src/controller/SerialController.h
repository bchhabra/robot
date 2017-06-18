#pragma once

#include <component/W.h>
#include "ActionList.h"

class SerialController {
	bool stopWasPressed = false;

public:
	void checkController() {
		if (Serial.available()) {
			String res = Serial.readStringUntil('\n');
			if (res == "s") {
				if (stopWasPressed) {
					changeStrategy(previousStrategy);
					stopWasPressed = false;
					return;
				}
				stopWasPressed = true;
			} else {
				stopWasPressed = false;
			}

			changeStrategy(&wifiStrategy);

			if (res == "f") {
				actionList.addAction(W::goForward, 0);
			}
			if (res == "b") {
				actionList.addAction(W::goBackward, 0);
			}
			if (res == "s") {
				actionList.addAction(W::doStop, 0);
			}
			if (res == "l") {
				actionList.addAction(W::goLeft, 0);
			}
			if (res == "tl") {
				actionList.addAction(W::turnLeft, 0);
			}
			if (res == "r") {
				actionList.addAction(W::goRight, 0);
			}
			if (res == "tr") {
				actionList.addAction(W::turnRight, 0);
			}
			if (res == "lb") {
				actionList.addAction(W::goLeftBack, 0);
			}
			if (res == "rb") {
				actionList.addAction(W::goRightBack, 0);
			}
		}
	}
};
