#include <Arduino.h>
#include <component/Lcd.h>
#include <controller/WiFi.h>

#include "controller/SerialController.h"
#include "strategy/RandomStrategy.h"
#include "ActionList.h"

#define LCD 0
#define DEBUG 1
#define SERIAL_CONTROLLER 0

#if SERIAL_CONTROLLER
SerialController controller;
#endif

#define PORT_CONTACTSENSORS 2

RandomStrategy randomstrategy;

volatile bool interruptCalled = false;

void setup() {
	lcdSetup();
	i2cSetup();
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);

	Serial.begin(9600);
	randomstrategy.init();
}

void loop() {

#if SERIAL_CONTROLLER
	controller.checkController();
#endif
	if (interruptCalled) {
		interruptCalled = false;
		W::doStop();
		actionList.removeAll();
		randomstrategy.obstacleFound();
	} else {
		if (actionList.isEmpty()) {
			randomstrategy.run();
		}
	}
	actionList.playNextAction();
}

void interrupt() {

	interruptCalled = true;
}
