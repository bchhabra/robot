// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define SERIAL_CONTROLLER 1

#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <RCSwitch.h>
#include "Wheel.h"
#include "RfController.h"
#include "SerialController.h"
#include "SonarSensor.h"

#if LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

#if SERIAL_CONTROLLER
SerialController controller;
#else
RfController controller;
#endif

Wheel left(8, 9);
Wheel right(6, 7);
SonarSensor front(12, 13);

boolean running = false;
int maxRange = 200;
int minRange = 20;
long duration, distance;
int delayTurn = 200;

void setup() {
  controller.setup();

#if LCD
  lcd.init();
  lcd.backlight();
#endif
}


void loop() {
  distance = front.getDistance();

  if (distance <= minRange && distance > 0) {
    if (running) {
      doStop();
      goLeftBack();
    } else {
      goRightBack();
    }
    delay(delayTurn*3);
  } else {
    doResume();
  }
  
  if (controller.available()) {
    Command cmd = controller.getReceivedCommand();
    switch (cmd) {
      case FORWARD:
        running = true;
        goForward();
        break;
      case LEFT_BACK:
        goLeftBack();
        break;
      case STOP: 
        running = false;
        doStop();
        break;
      case RIGHT_BACK: 
        goRightBack();
        break;
      case LEFT: 
        goLeft();
        break;
      case RIGHT: 
        goRight();
        break;
    }
  }
}

void doResume() {
  if (running) {
    goForward();
  } else {
    doStop();
  }
}

void goForward() {
  displayWheels("forward");
  left.forward();
  right.forward();
}

void goBackward() {
  running = true;
  displayWheels("backward");
  left.backward();
  right.backward();
}

void doStop() {
  displayWheels("stopped");
  left.stop();
  right.stop();
}

void goLeft() {
  displayWheels("left");
  left.stop();
  right.forward();
  delay(delayTurn);
  doResume();
}

void goLeftBack() {
  displayWheels("left back");
  left.stop();
  right.backward();
  delay(delayTurn);
  doResume();
}

void goRight() {
  displayWheels("right");
  left.forward();
  right.stop();
  delay(delayTurn);
  doResume();
}

void goRightBack() {
  displayWheels("right back");
  left.backward();
  right.stop();
  delay(delayTurn);
  doResume();
}

void displayWheels(String direction) {
#if LCD
  lcd.setCursor(0,0);
  lcd.print(direction + "          ");
#endif
}

