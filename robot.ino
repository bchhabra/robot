// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define DEBUG 1
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
SonarSensor leftSensor(13, 12);
SonarSensor frontSensor(13, 11);
SonarSensor rightSensor(13, 10);
Fifo fifo;

enum Direction {
  none, forward, backward
} direction = none;

int frontRange = 25;
int sideRange = 23;

void setup() {

#if LCD
  lcd.init();
  lcd.backlight();
#endif
#if DEBUG
  Serial.begin(9600);
#endif

  Wire.begin(0x30);             // join i2c bus with address #0x30
  // deactivate internal pullups for twi.
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
  Wire.onReceive(receiveEvent); // register event
  controller.setup();
  direction = forward;
  delay(5000);
  doResume();
}

void receiveEvent(int howMany) {
  String res = "";
  while (0 < Wire.available()) // loop through all but the last
  {
    res += (char)Wire.read(); // receive byte as a character
  }
  if (res == "f") w.goForward();
  if (res == "b") w.goBackward();
  if (res == "s") w.doStop();
  if (res == "l") w.goLeft();
  if (res == "tl") w.turnLeft();
  if (res == "r") w.goRight();
  if (res == "tr") w.turnRight();
  if (res == "lb") w.goLeftBack();
  if (res == "rb") w.goRightBack();
}


void loop() {
  checkController();

  movingSensing();
}

void handleLeftObstacle() {
  Obstacle* obst = fifo.getLastObstacle();
  if (obst->same(fifo.getObstacle(-1))) {
    w.doStop();
    w.goLeftBack();
  } else {
    w.goRight();
  }
  w.doStop();
}

void handleLeftFrontObstacle() {
  Obstacle* obst = fifo.getLastObstacle();
  if (obst->same(fifo.getObstacle(-1))) {
    w.turnRight();
  } else {
    w.goLeftBack();
  }
  w.doStop();
}

void handleRightObstacle() {
  Obstacle* obst = fifo.getLastObstacle();
  if (obst->same(fifo.getObstacle(-1))) {
    w.doStop();
    w.goRightBack();
  } else {
    w.goLeft();
  }
  w.doStop();
}

void handleRightFrontObstacle() {
  Obstacle* obst = fifo.getLastObstacle();
  if (obst->same(fifo.getObstacle(-1))) {
    w.turnLeft();
  } else {
    w.goRightBack();
  }
  w.doStop();
}

void handleFrontObstacle() {
  w.goLeftBack();
  w.doStop();
}

void handleAllObstacles() {
  Obstacle* obst = fifo.getLastObstacle();
  if (obst->same(fifo.getObstacle(-1))) {
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
        break;
      case 0x6:
        handleLeftFrontObstacle();
        break;
      case 0x1:
        handleRightObstacle();
        break;
      case 0x3:
        handleRightFrontObstacle();
        break;
      case 0x2:
        handleFrontObstacle();
        break;
      case 0x5:
      case 0x7:
        handleAllObstacles();
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
  
  if (!obstacle.isEmpty()) {
    fifo.addObstacle(&obstacle);
#ifdef DEBUG
    Serial.print("Obstacles detected: ");
    Serial.println(obstacle.getDirection());
#endif
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

