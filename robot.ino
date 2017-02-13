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


enum Direction {
	none, forward, backward
} direction = none;

void i2cSetup() {
	Wire.begin(0x30); // join i2c bus with address #0x30
	// deactivate internal pullups for twi.
	digitalWrite(SDA, LOW);
	digitalWrite(SCL, LOW);
	Wire.onReceive(receiveEvent); // register event
}

void setup() {

#if LCD
	lcd.init();
	lcd.backlight();
#endif

	i2cSetup();
    Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
}

void receiveEvent(int howMany) {
	String res = "";
	while (0 < Wire.available()) // loop through all but the last
	{
		res += (char) Wire.read(); // receive byte as a character
	}
	if (res == "f") {
		direction = forward;
		w.goForward();
	}
	if (res == "b") {
		direction = backward;
		w.goBackward();
	}
	if (res == "s") {
		direction = none;
		w.doStop();
	}
	if (res == "l")
		w.goLeft();
	if (res == "tl")
		w.turnLeft();
	if (res == "r")
		w.goRight();
	if (res == "tr")
		w.turnRight();
	if (res == "lb")
		w.goLeftBack();
	if (res == "rb")
		w.goRightBack();
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
