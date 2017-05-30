#pragma once
#include <Arduino.h>
#define WHEEL_SPEED 200

class Wheel {
	byte pin1;
	byte pin2;
	byte speedPin;
	byte speed;

	unsigned long previousTime = 0;
	unsigned long interval = 0;

	void scheduleStop(unsigned long delayTurn) {
		if (delayTurn > 0) {
			previousTime = millis();
			interval = delayTurn;
		}
	}

public:
	Wheel(byte pin1, byte pin2, byte speedPin) {
		this->pin1 = pin1;
		this->pin2 = pin2;
		this->speedPin = speedPin;
		this->speed = WHEEL_SPEED;
		pinMode(pin1, OUTPUT);
		pinMode(pin2, OUTPUT);
		pinMode(speedPin, OUTPUT);
	}

	void checkShouldStop() {
		unsigned long currentTime = millis();
		if ((previousTime > 0) && ((currentTime - previousTime) >= interval)) {
			stop();
		}
	}

	void stop() {
		previousTime = 0;
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
	}

	void forward(unsigned long delayTurn = 0) {
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, HIGH);
		analogWrite(speedPin, speed);
		scheduleStop(delayTurn);
	}

	void backward(unsigned long delayTurn = 0) {
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, LOW);
		analogWrite(speedPin, speed);
		scheduleStop(delayTurn);
	}

	void setSpeed(byte value) {
		this->speed = value;
		analogWrite(speedPin, value);
	}
};

