#include <Arduino.h>
#include <Wire.h> 
#include "Wheels.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"
#include "BoxStrategy.h"
#include "RandomStrategy.h"

#include "ActionList.h"
#include "I2C.h"
#include "Lcd.h"

#define LCD 0
#define DEBUG 1
#define SERIAL_CONTROLLER 0

#if SERIAL_CONTROLLER
SerialController controller;
#endif

#define PORT_CONTACTSENSORS 2

BoxStrategy strategy;
RandomStrategy randomstrategy;

volatile bool interruptCalled = false;

void setup() {
	lcdSetup();
	i2cSetup();
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);

	Serial.begin(9600);
	direction = forward;
	randomstrategy.init();
}

void loop() {

#if SERIAL_CONTROLLER
	controller.checkController();
#endif
	if (interruptCalled) {
		interruptCalled = false;
		W::doStop();
		actionList.empty();
		randomstrategy.obstacleFound();
	} else {
		if (actionList.isLastActionFinished()) {
			randomstrategy.run(doResume);
		}
	}
	actionList.playNextAction();
}

void interrupt() {

	interruptCalled = true;
}

void doResume() {

	switch (direction) {
	case none:
		w.doStop();
		break;
	case forward:
		w.goForward();
		break;
	case backward:
		w.goBackward();
		break;
	}
}
