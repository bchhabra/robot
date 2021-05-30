#include <Arduino.h>
#include <component/Lcd.h>
#include <controller/WiFiBridge.h>
#include <imu/MinIMU9AHRS.h>
#include <strategy/FactoryStrategy.h>
#include <strategy/PlayStrategy.h>

#include "controller/SerialController.h"
#include "component/SonarSensor.h"
#include "ActionList.h"

#ifdef  ESP8266
#include "ota.h"
#endif


#define LCD 0
#define SERIAL_CONTROLLER 0
#define TEST_IMU 0

#ifdef PROTOTYPE
#define SCAN_INTERVAL 30*1000
unsigned long lastScan = millis();
SonarSensor frontLeftSensor { 11, 10 };
#else
#define PORT_CONTACTSENSORS 2
#endif

#if SERIAL_CONTROLLER
SerialController controller;
#endif

#if TEST_IMU
int initialDeg;
#endif


volatile bool interruptCalled = false;

void interrupt();

void setup() {
	lcdSetup();
#if TEST_IMU
	I2C_Init();
	imu_setup();
	initialDeg = readAngle();
#endif
#ifdef WIFI_BRIDGE
	i2cSetup();
#endif
#ifdef  ESP8266
    setupOTA();
#endif

	Serial.begin(9600);

#ifdef PROTOTYPE
	changeStrategy(&playStrategy);
#else
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
	changeStrategy(&factoryStrategy);
#endif
}

void loop() {
#ifdef  ESP8266
	handleOTA();
#endif
#if SERIAL_CONTROLLER
	controller.checkController();
#endif
#if TEST_IMU
	imu_loop();
#endif
	unsigned long currentTime = millis();
	if (interruptCalled) {
		interruptCalled = false;
		activeStrategy->obstacleFound(currentTime);
	} else {
		activeStrategy->run();
	}
	actionList.playNextAction();

#ifdef PROTOTYPE
	if (!interruptCalled && ((currentTime - lastScan) > SCAN_INTERVAL)) {
		lastScan = currentTime;
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
