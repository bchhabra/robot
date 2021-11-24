#pragma once

#include "Controller.h"
#include <component/Leds.h>

#define UP_THRESHOLD 700
#define DOWN_THRESHOLD 300
#define IS_NEUTRAL(x) (DOWN_THRESHOLD < x  && x < UP_THRESHOLD)
#define IS_ABOVE(x) (x >= UP_THRESHOLD)
#define IS_BELOW(x) (x <= DOWN_THRESHOLD)

class BlueController: public Controller {
	bool connected = false;

	Command getReceivedCommand() {
		String value = Serial.readStringUntil('\n');
		int xAxis, yAxis, button = 0;
		sscanf(value.c_str(), "%d, %d, %d", &xAxis, &yAxis, &button);
		
		if ((button == 0) && IS_NEUTRAL(yAxis) && IS_NEUTRAL(xAxis)) return TOGGLE_SENSORS;
		if ((button == 1) && IS_NEUTRAL(yAxis) && IS_NEUTRAL(xAxis)) return STOP;

		if (IS_ABOVE(yAxis) && IS_NEUTRAL(xAxis)) return FORWARD;
		if (IS_BELOW(yAxis) && IS_NEUTRAL(xAxis)) return BACKWARD;
		if (IS_NEUTRAL(yAxis) && IS_ABOVE(xAxis)) return TURN_RIGHT;
		if (IS_NEUTRAL(yAxis) && IS_BELOW(xAxis)) return TURN_LEFT;
		
		if (IS_ABOVE(yAxis) && IS_ABOVE(xAxis)) return RIGHT;
		if (IS_ABOVE(yAxis) && IS_BELOW(xAxis)) return LEFT;
		if (IS_BELOW(yAxis) && IS_ABOVE(xAxis)) return RIGHT_BACK;
		if (IS_BELOW(yAxis) && IS_BELOW(xAxis)) return LEFT_BACK;
		
		return NONE;
	}

	bool available() {
		bool state = digitalRead(BLUE_STATE_PIN);
		if (state != connected) {
			connected = state;
			if (connected) {
				runMode = FULL_MANUAL;
				actionList.removeAll();
				W::doStop();
				Leds::allOff();
				serial.println("connected");
			} else {
				runMode = AUTO;
				serial.println("disconnected");
			}
		}
		return Serial.available();
	}

public:
	void setup() {
		pinMode(BLUE_STATE_PIN, INPUT);
		Serial.begin(9600);
	}
	
};
