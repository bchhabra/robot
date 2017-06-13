#pragma once

#include <Wire.h>
#include "ActionList.h"
#include "component/W.h"
#include "strategy/WifiStrategy.h"

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

void i2cSetup() {
	Wire.begin(0x30); // join i2c bus with address #0x30
	// deactivate internal pullups for twi.
	digitalWrite(SDA, LOW);
	digitalWrite(SCL, LOW);
	Wire.onReceive(receiveEvent); // register event
}
