#pragma once

#if CONTROLLER & CTRL_SERIAL

#include "Controller.h"

class SerialController: public Controller {

	Command getReceivedCommand() override {
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
		return NONE;
	}

	bool available() override {
		return Serial.available();
	}
	
} controller;
#endif