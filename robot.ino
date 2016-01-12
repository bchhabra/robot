// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define SERIAL_CONTROLLER 1

#if LCD
#include <LiquidCrystal_I2C.h>
#endif
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
SonarSensor leftSensor(10, 13);
SonarSensor frontSensor(10, 12);
SonarSensor rightSensor(10, 11);

enum Direction {
  none, forward, backward
} direction = none;

int frontRange = 20;
int sideRange = 10;
int delayTurn = 200;

void setup() {

#if LCD
  lcd.init();
  lcd.backlight();
#endif

  controller.setup();
}


void loop() {
  checkController();

  Direction prevDirection = direction;

  if (direction == none) {
    notMovingSensing();
  } else {
    movingSensing();
  }
  
  direction = prevDirection;
  doResume();
}

void movingSensing() {
  boolean obstacle = false;
 
  frontSensor.sendSignal();  
  if (frontSensor.isInRange(frontRange)) {
    obstacle = true;
    doStop();
  } else {
    leftSensor.sendSignal();  
    if (leftSensor.isInRange(sideRange)) {
      obstacle = true;
      goRight();
    }
  
    rightSensor.sendSignal();  
    if (rightSensor.isInRange(sideRange)) {
      obstacle = true;
      goLeft();
    }
  }
  
  if (obstacle) {
    delay(600);
  }
}

boolean notMovingSensing() {
  boolean obstacle = false;
 
  frontSensor.sendSignal();  
  if (frontSensor.isInRange(frontRange)) {
    goBackward();
    obstacle = true;
  }

  leftSensor.sendSignal();  
  if (leftSensor.isInRange(sideRange)) {
    goRightBack();
    obstacle = true;
  }

  rightSensor.sendSignal();  
  if (rightSensor.isInRange(sideRange)) {
    goLeftBack();
    obstacle = true;
  }

  return obstacle;  
}

void checkController() {
  if (controller.available()) {
    Command cmd = controller.getReceivedCommand();
    switch (cmd) {
      case FORWARD:
        goForward();
        break;
      case BACKWARD:
        goBackward();
        break;
      case STOP:
        doStop();
        break;
      case LEFT: 
        goLeft();
        break;
      case RIGHT: 
        goRight();
        break;
      case LEFT_BACK:
        goLeftBack();
        break;
      case RIGHT_BACK: 
        goRightBack();
        break;
    }
  }
}

void doResume() {
  switch (direction) {
    case none:
      doStop();
      break;
    case forward:
      goForward();
      break;
    case backward:
      goBackward();
      break;
  }
}

void goForward() {
  direction = forward;
  displayWheels("forward");
  left.forward();
  right.forward();
}

void goBackward() {
  direction = backward;
  displayWheels("backward");
  left.backward();
  right.backward();
}

void doStop() {
  direction = none;
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

