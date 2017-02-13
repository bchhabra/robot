#pragma once

void receiveEvent(int howMany) {
	String res = "";
	while (0 < Wire.available()) // loop through all but the last
	{
		res += (char) Wire.read(); // receive byte as a character
	}
	if (res == "f") {
		direction = forward;
		w.goForward();
	}
	if (res == "b") {
		direction = backward;
		w.goBackward();
	}
	if (res == "s") {
		direction = none;
		w.doStop();
	}
	if (res == "l")
		w.goLeft();
	if (res == "tl")
		w.turnLeft();
	if (res == "r")
		w.goRight();
	if (res == "tr")
		w.turnRight();
	if (res == "lb")
		w.goLeftBack();
	if (res == "rb")
		w.goRightBack();
}

void i2cSetup() {
	Wire.begin(0x30); // join i2c bus with address #0x30
	// deactivate internal pullups for twi.
	digitalWrite(SDA, LOW);
	digitalWrite(SCL, LOW);
	Wire.onReceive(receiveEvent); // register event
}
