#include <Arduino.h>

#include "Pins.h"
#include "RunMode.h"
#include "ActionList.h"

#include "Robot.h"
#include "Prototype.h"

#include <component/Lcd.h>
#include "controller/WiFiBridge.h"
#include "controller/SerialController.h"
#include "controller/BlueController.h"
#include "controller/EmptyController.h"
#include <imu/MinIMU9AHRS.h>
#include "wifi.h"
#include "ota.h"


void setup() {
	Serial.begin(9600);

	Lcd::setup();
	Imu::setup();
	WifiBridge::setup();
	Wifi::setup();
    Ota::setup();
	controller.setup();

	runMode = RunMode::AUTO;

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
	yield();
}
