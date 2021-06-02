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
#define SCAN_INTERVAL 35
unsigned long lastScan = 0;
SonarSensor frontLeftSensor { 11, 10 };
SonarSensor frontRightSensor { 4, 12 };
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
unsigned long currentTime = 0;

void interrupt();
Obstacle* searchObstacle();

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
	// changeStrategy(&playStrategy);
#else
	attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
	changeStrategy(&factoryStrategy);
#endif
}

void loop() {
	currentTime = millis();
#ifdef  ESP8266
	handleOTA();
#endif
#if SERIAL_CONTROLLER
	controller.checkController();
#endif
#if TEST_IMU
	imu_loop();
#endif

#ifdef PROTOTYPE
	if ((currentTime - lastScan) > SCAN_INTERVAL) {
		static byte sensorIndex = 0;
		static Obstacle* frontLeft;

		sensorIndex %= 2;
		if (sensorIndex == 0) {
			frontLeft = frontLeftSensor.scan();
		} else {
			SonarObstacles obstacles = SonarObstacles(frontLeft, frontRightSensor.scan());
			if (!obstacles.isEmpty()) {
				playStrategy.obstacleFound(obstacles);
			}
		}
		sensorIndex++;
		lastScan = currentTime;
	}
#else
	if (interruptCalled) {
		interruptCalled = false;
		activeStrategy->obstacleFound(new Obstacle(0, currentTime));
		delete obstacle;
	}
#endif
	actionList.playNextAction();
}

void interrupt() {
	interruptCalled = true;
}
