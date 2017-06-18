#include <Arduino.h>
#include <component/Lcd.h>
#include <controller/WiFi.h>
#include <imu/MinIMU9AHRS.h>
#include <strategy/FactoryStrategy.h>

#include "controller/SerialController.h"
#include "component/SonarSensor.h"
#include "ActionList.h"


#define LCD 0
#define SERIAL_CONTROLLER 0
#define TEST_IMU 1

#define PORT_CONTACTSENSORS 2

#if SERIAL_CONTROLLER
SerialController controller;
#endif
#if TEST_IMU
int initialDeg;
#endif

#ifdef PROTOTYPE
SonarSensor frontLeftSensor { 11, 10 };
#endif

volatile bool interruptCalled = false;

void setup() {
	lcdSetup();
	i2cSetup();
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
#if TEST_IMU
	imu_setup();
	initialDeg = readAngle();
#endif

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
#if TEST_IMU
	imu_loop();
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
