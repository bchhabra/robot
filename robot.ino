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
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);

	Serial.begin(9600);
	// boot loader of pro-mini needs this so that it knows data sent is not a program
	// https://www.arduino.cc/en/Main/arduinoBoardProMini - Automatic (Software) Reset
	delay(1000);
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
