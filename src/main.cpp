#include <Arduino.h>
#include <component/Lcd.h>
#include "component/Piezzo.h"
#include "controller/WiFiBridge.h"
#include "controller/SerialController.h"
#include "controller/BlueController.h"
#include "controller/EmptyController.h"
#include <imu/MinIMU9AHRS.h>
#include "ota.h"
#include "RunMode.h"

#include "ActionList.h"
#include "Robot.h"
#include "Prototype.h"


#if SERIAL_CONTROLLER
SerialController controller;
#elif BLUE_CONTROLLER
BlueController controller;
#else
EmptyController controller;
#endif

void setup() {
	// Sound::play2();
	// Sound::play();
	Lcd::setup();
	Imu::setup();
	WifiBridge::setup();
    Ota::setup();
	controller.setup();

	Serial.begin(9600);

	Run::setMode(RunMode::AUTO);

	Robot::setup();
	serial.println("starting...");
}

void loop() {
	Ota::handle();
	controller.checkController();
	Imu::loop();
	
	Robot::loop(millis());
	
	actionList.playNextAction();
	actionList2.playNextAction();
}
