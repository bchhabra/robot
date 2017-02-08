#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "Wheels.h"

#define PORT_CONTACTSENSORS 2

class RandomStrategy: public Strategy {
public:
	void run(void (*f)()) {
		// implement logic
	}

	void obstacleFound() {
		w.goBackward(100);
		w.turnRight(100);
	}
};
