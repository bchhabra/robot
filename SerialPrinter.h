#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>

class SerialPrinter {
	unsigned long previousTime = 0;
public:
	void println(const char* message) {
		unsigned long currentTime = millis();
		if (currentTime - previousTime > 100) {
			Serial.println(message);
			previousTime = currentTime;
		}
	}
} serial;
