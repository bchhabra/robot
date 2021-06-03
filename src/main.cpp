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
SonarSensor frontLeftSensor { FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO };
SonarSensor frontRightSensor { FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO };
void updateLeds(Obstacle* obstacle, uint8_t pinClose, uint8_t pinFar);
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
	pinMode(PIN_LEFT_FAR, OUTPUT);
	pinMode(PIN_LEFT_CLOSE, OUTPUT);
	pinMode(PIN_RIGHT_FAR, OUTPUT);
	pinMode(PIN_RIGHT_CLOSE, OUTPUT);
	digitalWrite(PIN_LEFT_FAR, HIGH);
	digitalWrite(PIN_LEFT_CLOSE, HIGH);
	digitalWrite(PIN_RIGHT_FAR, HIGH);
	digitalWrite(PIN_RIGHT_CLOSE, HIGH);
	delay(500);
	digitalWrite(PIN_LEFT_FAR, LOW);
	digitalWrite(PIN_LEFT_CLOSE, LOW);
	digitalWrite(PIN_RIGHT_FAR, LOW);
	digitalWrite(PIN_RIGHT_CLOSE, LOW);
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

	currentTime = millis();
#ifdef PROTOTYPE
	if (currentTime >= lastScan) {
		static byte sensorIndex = 0;
		static bool isWaiting = false;
		static Obstacle* frontLeft;
		static Obstacle* frontRight;
		static SonarObstacles obstacles = SonarObstacles();

		sensorIndex %= 2;
		if (sensorIndex == 0) {
			frontLeft = frontLeftSensor.scan();
			updateLeds(frontLeft, PIN_LEFT_CLOSE, PIN_LEFT_FAR);
			if (isWaiting) {
				isWaiting = false;
				obstacles.frontLeft = frontLeft;
				playStrategy.obstacleFound(obstacles);
				obstacles.deleteObstacles();
			} else if (frontRight != NULL) {
				isWaiting = true;
				obstacles.frontRight = frontRight;
				playStrategy.obstacleFound(obstacles);
			} else {
				delete frontLeft;
			}
		} else {
			frontRight = frontRightSensor.scan();
			updateLeds(frontRight, PIN_RIGHT_CLOSE, PIN_RIGHT_FAR);
			if (isWaiting) {
				isWaiting = false;
				obstacles.frontRight = frontRight;
				playStrategy.obstacleFound(obstacles);
				obstacles.deleteObstacles();
			} else if (frontRight != NULL) {
				isWaiting = true;
				obstacles.frontRight = frontRight;
				playStrategy.obstacleFound(obstacles);
			} else {
				delete frontRight;
			}
		}
		sensorIndex++;
		lastScan = millis() + SCAN_INTERVAL;
	}
#else
	if (interruptCalled) {
		interruptCalled = false;
		Obstacle* obstacle = new Obstacle(0, currentTime);
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
void updateLeds(Obstacle* obstacle, uint8_t pinClose, uint8_t pinFar) {
	if (obstacle != NULL) {
		if (obstacle->isInRange(OBSTACLE_RANGE)) {
			digitalWrite(pinClose, HIGH);
			digitalWrite(pinFar, HIGH);
		} else if (obstacle->isInRange(MAX_DISTANCE)) {
			digitalWrite(pinClose, LOW);
			digitalWrite(pinFar, HIGH);
		} else {
			digitalWrite(pinClose, LOW);
			digitalWrite(pinFar, LOW);
		}
	} else {
		digitalWrite(pinClose, LOW);
		digitalWrite(pinFar, LOW);
	}
}
#endif
