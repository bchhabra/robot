#pragma once

#include <Arduino.h>
#include "Strategy.h"
#include "Wheels.h"

#define PORT_CONTACTSENSORS 2

void obstacleFound() {
	w.goBackward();
	delay(1000);
	w.goRight();
	delay(1000);
}

class RandomStrategy : public Strategy {
  public:
    void init() {
    	attachInterrupt( digitalPinToInterrupt(PORT_CONTACTSENSORS), obstacleFound, FALLING);
    }

    void run(void (*f)()) {
    	w.goForward();
    }
};
