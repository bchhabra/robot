// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define DEBUG 0
#define SERIAL_CONTROLLER 0

#if LCD
#include <LiquidCrystal_I2C.h>
#endif
#include <Wire.h> 
#include <RCSwitch.h>
#include "Wheels.h"
#include "RfController.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"

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
Fifo fifo;

enum Direction {
  none, forward, backward
} direction = none;

int frontRange = 25;
int sideRange = 23;
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

void handleLeftObstacle() {
  w.goRight();
  w.doStop();
}

void handleLeftFrontObstacle() {
  stuck ? w.turnRight() : w.goLeftBack();
  w.doStop();
}

void handleRightObstacle() {
  w.goLeft();
  w.doStop();
}

void handleRightFrontObstacle() {
  stuck ? w.turnLeft() : w.goRightBack();
  w.doStop();
}

void handleFrontObstacle() {
  w.goLeftBack();
  w.doStop();
}

void handleAllObstacles() {
  if (stuck) {
    w.turnRight();
  } else {
    w.goBackward();
    delay(500);
  }
  w.doStop();
}

void movingSensing() {
  detectObstacles();
  byte obstacle = fifo.getLastObstacle()->getDirection();
  if (obstacle) {
    switch (obstacle) {
      case 0x4:
        handleLeftObstacle();
        stuck = false;
        break;
      case 0x6:
        handleLeftFrontObstacle();
        stuck = false;
        break;
      case 0x1:
        handleRightObstacle();
        stuck = false;
        break;
      case 0x3:
        handleRightFrontObstacle();
        stuck = false;
        break;
      case 0x2:
        handleFrontObstacle();
        stuck = false;
        break;
      case 0x5:
      case 0x7:
        handleAllObstacles();
        stuck = true;
        break;
    }
    delay(600);
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

void detectObstacles() {
  Obstacle obstacle;
  long distance;
  
  frontSensor.sendSignal();
  distance = frontSensor.isInRange(frontRange);
  if (distance) {
    obstacle.addFront(distance);
  }
  leftSensor.sendSignal();
  distance = leftSensor.isInRange(sideRange);
  if (distance) {
    obstacle.addLeft(distance);
  }
  
  rightSensor.sendSignal();
  distance = rightSensor.isInRange(sideRange);
  if (distance) {
    obstacle.addRight(distance);
  }
  fifo.addObstacle(&obstacle);

#if DEBUG
  Serial.print("Obstacles detected: ");
  Serial.println(obstacle.getDirection());
#endif
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

