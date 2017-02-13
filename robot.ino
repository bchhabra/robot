#define LCD 0
#define DEBUG 1
#define SERIAL_CONTROLLER 0

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include "Wheels.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"
#include "BoxStrategy.h"
#include "RandomStrategy.h"
#include "time.h"
#include "I2C.h"


#if LCD
LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

#if SERIAL_CONTROLLER
SerialController controller;
#endif

BoxStrategy strategy;
RandomStrategy randomstrategy;

volatile bool interruptCalled = false;
int interruptCounter = 0;
time_t startTime=time(NULL);
time_t interruptTime;
time_t lastinterruptTime;


void setup() {

#if LCD
	lcd.init();
	lcd.backlight();
#endif

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
		double timediff = difftime(interruptTime, lastinterruptTime);
		randomstrategy.obstacleFound(interruptCounter,timediff);
	}
}

void interrupt() {
	interruptTime=time(NULL);
	interruptCounter++;
	interruptCalled = true;
}

void doResume() {
	lastinterruptTime=interruptTime;
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

void displayWheels(String direction) {
#if LCD
	lcd.setCursor(0,0);
	lcd.print(direction + "          ");
#endif
}
