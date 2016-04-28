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
#include "Wheels.h"
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

Wheels w(new Wheel(8, 9), new Wheel(6, 7));
SonarSensor leftSensor(10, 13);
SonarSensor frontSensor(10, 12);
SonarSensor rightSensor(10, 11);

enum Direction {
  none, forward, backward
} direction = none;

int frontRange = 20;
int sideRange = 10;

void setup() {

#if LCD
  lcd.init();
  lcd.backlight();
#endif

  controller.setup();
  w.goForward();
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
    w.doStop();
    w.goLeftBack();
    w.doStop();
  } else {
    leftSensor.sendSignal();  
    if (leftSensor.isInRange(sideRange)) {
      obstacle = true;
      //goRight();
      w.goLeftBack();
      w.doStop();
    }
  
    rightSensor.sendSignal();  
    if (rightSensor.isInRange(sideRange)) {
      obstacle = true;
      //goLeft();
      w.goRightBack();
      w.doStop();
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
    obstacle = true;
    w.goBackward();
    w.doStop();
  }

  leftSensor.sendSignal();  
  if (leftSensor.isInRange(sideRange)) {
    obstacle = true;
    w.goRightBack();
    w.doStop();
  }

  rightSensor.sendSignal();  
  if (rightSensor.isInRange(sideRange)) {
    obstacle = true;
    w.goLeftBack();
    w.doStop();
  }

  return obstacle;  
}

void doResume() {
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

void checkController() {
  if (controller.available()) {
    Command cmd = controller.getReceivedCommand();
    switch (cmd) {
      case FORWARD:
        w.goForward();
        break;
      case BACKWARD:
        w.goBackward();
        break;
      case STOP:
        w.doStop();
        break;
      case LEFT: 
        w.goLeft();
        break;
      case RIGHT: 
        w.goRight();
        break;
      case LEFT_BACK:
        w.goLeftBack();
        break;
      case RIGHT_BACK: 
        w.goRightBack();
        break;
    }
  }
}

