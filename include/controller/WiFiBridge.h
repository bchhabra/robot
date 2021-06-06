#pragma once

#include <Wire.h>
#include "ActionList.h"
#include "component/W.h"
#include "strategy/WifiStrategy.h"

namespace WifiBridge {

bool stopWasPressed = false;

void receiveEvent(int howMany) {
	String res = "";
	while (0 < Wire.available()) // loop through all but the last
	{
		res += (char) Wire.read(); // receive byte as a character
	}

	actionList.removeAll();
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
		actionList.addTimedAction(W::goForward, 0);
	}
	if (res == "b") {
		actionList.addTimedAction(W::goBackward, 0);
	}
	if (res == "s") {
		actionList.addTimedAction(W::doStop, 0);
	}
	if (res == "l") {
		actionList.addTimedAction(W::goLeft, 0);
	}
	if (res == "tl") {
		actionList.addTimedAction(W::turnLeft, 0);
	}
	if (res == "r") {
		actionList.addTimedAction(W::goRight, 0);
	}
	if (res == "tr") {
		actionList.addTimedAction(W::turnRight, 0);
	}
	if (res == "lb") {
		actionList.addTimedAction(W::goLeftBack, 0);
	}
	if (res == "rb") {
		actionList.addTimedAction(W::goRightBack, 0);
	}
}

void setup() {
#if WIFI_BRIDGE
	Wire.begin(0x30); // join i2c bus with address #0x30
	// deactivate internal pullups for twi.
	digitalWrite(SDA, LOW);
	digitalWrite(SCL, LOW);
	Wire.onReceive(receiveEvent); // register event
#endif
}

}