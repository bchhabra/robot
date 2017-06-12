#include <Arduino.h>
#include <component/Lcd.h>
#include <controller/WiFi.h>
#include <strategy/FactoryStrategy.h>

#include "controller/SerialController.h"
#include "ActionList.h"

#define LCD 0
#define DEBUG 1
#define SERIAL_CONTROLLER 0

#if SERIAL_CONTROLLER
SerialController controller;
#endif

#define PORT_CONTACTSENSORS 2

volatile bool interruptCalled = false;

void setup() {
	lcdSetup();
	i2cSetup();
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);

	Serial.begin(9600);

	changeStrategy(&factoryStrategy);
}

void loop() {

#if SERIAL_CONTROLLER
	controller.checkController();
#endif
	if (interruptCalled) {
		interruptCalled = false;
		activeStrategy->obstacleFound();
	} else {
		activeStrategy->run();
	}
	actionList.playNextAction();
}

void interrupt() {

	interruptCalled = true;
}
