#include <Arduino.h>
#include <component/Lcd.h>
#include "component/SonarSensor.h"
#include "component/Leds.h"
#include <controller/WiFiBridge.h>
#include "controller/SerialController.h"
#include <imu/MinIMU9AHRS.h>
#include "ota.h"

#include <strategy/FactoryStrategy.h>
#include <strategy/PlayStrategy.h>

#include "ActionList.h"


#ifdef PROTOTYPE
#define SCAN_INTERVAL 35
unsigned long lastScan = 0;
SonarSensor frontLeftSensor { FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO };
SonarSensor frontRightSensor { FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO };
void applyStrategy(SonarObstacles& obstacles);
#endif


volatile bool interruptCalled = false;
unsigned long currentTime = 0;

void interrupt();

void setup() {
	Lcd::setup();
	Imu::setup();
	WifiBridge::setup();
    Ota::setup();
	Leds::setup();

	Serial.begin(9600);

#ifndef PROTOTYPE
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
	changeStrategy(&factoryStrategy);
#endif
}

void loop() {
	Ota::handle();
	controller.checkController();
	Imu::loop();

	currentTime = millis();
#ifdef PROTOTYPE
	if (currentTime >= lastScan) {
		static byte sensorIndex = 0;
		static SonarObstacles obstacles = SonarObstacles();

		if (sensorIndex == 0) {
			obstacles.frontLeft = frontLeftSensor.scan();
			Leds::updateLeft(obstacles);
			applyStrategy(obstacles);
		} else {
			obstacles.frontRight = frontRightSensor.scan();
			Leds::updateRight(obstacles);
			applyStrategy(obstacles);
		}
		++sensorIndex %= 2;
		lastScan = millis() + SCAN_INTERVAL;
	}
#else
	if (interruptCalled) {
		interruptCalled = false;
		Obstacle* obstacle = new Obstacle(currentTime);
		activeStrategy->obstacleFound(obstacle);
		delete obstacle;
	} else {
		activeStrategy->run();
	}
#endif
	actionList.playNextAction();
}

void interrupt() {
	interruptCalled = true;
}

#ifdef PROTOTYPE
void applyStrategy(SonarObstacles& obstacles) {
	static bool secondCall = false;
	
	// first call, with only one obstacle scanned
	// second call, with both obstacles scanned
	playStrategy.obstacleFound(obstacles);
	if (secondCall) {
		obstacles.deleteObstacles();
	}
	secondCall = !secondCall;
}
#endif
