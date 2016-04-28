// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define DEBUG 0
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

#define DELAY_TURN 160

Wheels w(new Wheel(8, 9), new Wheel(6, 7), DELAY_TURN);
SonarSensor leftSensor(10, 13);
SonarSensor frontSensor(10, 12);
SonarSensor rightSensor(10, 11);

enum Direction {
  none, forward, backward
} direction = none;

int frontRange = 20;
int sideRange = 30;
boolean stuck = false;

void setup() {

#if LCD
  lcd.init();
  lcd.backlight();
#endif
#if DEBUG
  Serial.begin(9600);
#endif

  controller.setup();
  direction = forward;
  delay(5000);
}


void loop() {
  checkController();

  movingSensing();
}

void avoidLeftObstacle() {
  w.turnRight();
  w.doStop();
}

void solveLeftObstacle() {
  stuck ? w.turnRight() : w.goLeftBack();
  w.doStop();
}

void avoidRightObstacle() {
  w.turnLeft();
  w.doStop();
}

void solveRightObstacle() {
  stuck ? w.turnLeft() : w.goRightBack();
  w.doStop();
}

void avoidFrontObstacle() {
  w.goLeftBack();
  w.doStop();
}

void solveAllObstacles() {
  w.goBackward();
  delay(500);
  w.doStop();
}

void movingSensing() {
  byte obstacle = detectObstacles();
  if (obstacle) {
    w.doStop();
    delay(600);
    switch (obstacle) {
      case 0x4:
        avoidLeftObstacle();
        stuck = false;
        break;
      case 0x6:
        solveLeftObstacle();
        stuck = false;
        break;
      case 0x1:
        avoidRightObstacle();
        stuck = false;
        break;
      case 0x3:
        solveRightObstacle();
        stuck = false;
        break;
      case 0x2:
        avoidFrontObstacle();
        stuck = false;
        break;
      case 0x5:
      case 0x7:
        solveAllObstacles();
        stuck = true;
        break;
    }
  } else {
    doResume();
  }
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

byte detectObstacles() {
  byte obstacles = 0;
  frontSensor.sendSignal();
  if (frontSensor.isInRange(frontRange)) {
    obstacles |= 0x02;
  }
  leftSensor.sendSignal();
  if (leftSensor.isInRange(sideRange)) {
    obstacles |= 0x04;
  }
  
  rightSensor.sendSignal();
  if (rightSensor.isInRange(sideRange)) {
    obstacles |= 0x01;
  }


#if DEBUG
  Serial.print("Obstacles detected: ");
  Serial.println(obstacles);
#endif
  return obstacles;
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

