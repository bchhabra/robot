#pragma once

void receiveEvent(int howMany) {
	String res = "";
	while (0 < Wire.available()) // loop through all but the last
	{
		res += (char) Wire.read(); // receive byte as a character
	}
	if (res == "f") {
		actionList.removeAll();
		actionList.addAction(new Action(W::goForward, 0));
	}
	if (res == "b") {
		actionList.addAction(new Action(W::goBackward, 0));
	}
	if (res == "s") {
		actionList.addAction(new Action(W::doStop, 0));
	}
	if (res == "l") {
		actionList.addAction(new Action(W::goLeft, 0));
	}
	if (res == "tl") {
		actionList.addAction(new Action(W::turnLeft, 0));
	}
	if (res == "r") {
		actionList.addAction(new Action(W::goRight, 0));
	}
	if (res == "tr") {
		actionList.addAction(new Action(W::turnRight, 0));
	}
	if (res == "lb") {
		actionList.addAction(new Action(W::goLeftBack, 0));
	}
	if (res == "rb") {
		actionList.addAction(new Action(W::goRightBack, 0));
	}
}

void i2cSetup() {
	Wire.begin(0x30); // join i2c bus with address #0x30
	// deactivate internal pullups for twi.
	digitalWrite(SDA, LOW);
	digitalWrite(SCL, LOW);
	Wire.onReceive(receiveEvent); // register event
}
