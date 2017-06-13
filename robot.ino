#include <Arduino.h>
#include <component/Lcd.h>
#include <controller/WiFi.h>
#include <strategy/FactoryStrategy.h>

#include "controller/SerialController.h"
#include "component/SonarSensor.h"
#include "ActionList.h"

#define LCD 0
#define SERIAL_CONTROLLER 0

#if SERIAL_CONTROLLER
SerialController controller;
#endif

#define PORT_CONTACTSENSORS 2

#ifdef PROTOTYPE
SonarSensor frontLeftSensor { 11, 10 };
#endif
volatile bool interruptCalled = false;

void setup() {
	lcdSetup();
	i2cSetup();
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);

	Serial.begin(9600);

	changeStrategy(&factoryStrategy);
#ifdef PROTOTYPE
	changeStrategy(&wifiStrategy);
#endif
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

#ifdef PROTOTYPE
	if (!interruptCalled) {
		frontLeftSensor.scan();
		if (frontLeftSensor.isInRange(15)) {
			interruptCalled = true;
		}
	}
#endif
}

void interrupt() {

	interruptCalled = true;
}
