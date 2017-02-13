#define LCD 0
#define DEBUG 1
#define SERIAL_CONTROLLER 0

#include <Arduino.h>
#include <Wire.h> 
#include "Wheels.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"
#include "BoxStrategy.h"
#include "RandomStrategy.h"
#include "time.h"
#include "I2C.h"
#include "Lcd.h"


#if SERIAL_CONTROLLER
SerialController controller;
#endif

BoxStrategy strategy;
RandomStrategy randomstrategy;

volatile bool interruptCalled = false;



void setup() {
	lcdSetup();
	i2cSetup();
    Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
}

void loop() {

#if SERIAL_CONTROLLER
	controller.checkController();
#endif
	randomstrategy.run(doResume);
	if (interruptCalled) {
		interruptCalled = false;
		randomstrategy.obstacleFound();

	}
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
