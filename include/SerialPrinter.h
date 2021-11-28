#pragma once

#include <HardwareSerial.h>

class SerialPrinter {
	unsigned long previousTime = 0;
	unsigned int counter = 0;
public:
	void println(const char* message) {
#if DEBUG
		if (counter++ == 0) {
			previousTime = millis();
			Serial.println(message);
		} else {
			if (counter < 5) {
				Serial.println(message);
			} else {
				unsigned long currentTime = millis();
				if (currentTime - previousTime > 500) {
					counter = 0;
				}
			}
		}
#endif
	}
} serial;
