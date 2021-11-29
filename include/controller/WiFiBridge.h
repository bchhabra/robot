#pragma once

#include <Wire.h>
#include "ActionList.h"
#include "component/Wheels.h"
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
		actionList.addTimedAction(Wheels::goForward, 0);
	}
	if (res == "b") {
		actionList.addTimedAction(Wheels::goBackward, 0);
	}
	if (res == "s") {
		actionList.addTimedAction(Wheels::doStop, 0);
	}
	if (res == "l") {
		actionList.addTimedAction(Wheels::goLeft, 0);
	}
	if (res == "tl") {
		actionList.addTimedAction(Wheels::turnLeft, 0);
	}
	if (res == "r") {
		actionList.addTimedAction(Wheels::goRight, 0);
	}
	if (res == "tr") {
		actionList.addTimedAction(Wheels::turnRight, 0);
	}
	if (res == "lb") {
		actionList.addTimedAction(Wheels::goLeftBack, 0);
	}
	if (res == "rb") {
		actionList.addTimedAction(Wheels::goRightBack, 0);
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