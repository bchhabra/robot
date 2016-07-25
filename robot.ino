// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define DEBUG 1
#if LCD
#include <LiquidCrystal_I2C.h>
#endif
#include <Wire.h> 
#include "Wheels.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"

#if LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

SerialController controller;

#define DELAY_TURN 160
Wheel leftWheel(8, 9, 5);
Wheel rightWheel(6, 7, 3);

Wheels w(&leftWheel, &rightWheel, DELAY_TURN);
SonarSensor frontLeftSensor(11, 10);
SonarSensor frontRightSensor(4, 12);
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

  leftWheel.setSpeed(128);  
  rightWheel.setSpeed(128); 
  controller.setup();
  direction = none; // change this to forward if you want to move on startup
//  delay(5000);
  doResume();
}

void receiveEvent(int howMany) {
  String res = "";
  while (0 < Wire.available()) // loop through all but the last
  {
    res += (char)Wire.read(); // receive byte as a character
  }
  if (res == "f") direction = forward; w.goForward();
  if (res == "b") direction = backward; w.goBackward();
  if (res == "s") direction = none; w.doStop();
  if (res == "l") w.goLeft();
  if (res == "tl") w.turnLeft();
  if (res == "r") w.goRight();
  if (res == "tr") w.turnRight();
  if (res == "lb") w.goLeftBack();
  if (res == "rb") w.goRightBack();
}


void loop() {
//  checkController();

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
  w.goBackward();
  delay(250);
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
  
  frontRightSensor.scan();
  delay(25);
  frontLeftSensor.scan();
  delay(25);

  distance = frontRightSensor.isInRange(frontRange);
  if (distance) {
    obstacle.addFront(distance);
  }

  distance = frontLeftSensor.isInRange(frontRange);
  if (distance) {
    obstacle.addLeft(distance);
  }
  
  
  if (!obstacle.isEmpty()) {
    fifo.addObstacle(&obstacle);
  }
#ifdef DEBUG
    Serial.print("Obstacles detected = ");
    Serial.print(obstacle.getDirection());
    Serial.print("; left = ");
    Serial.print(obstacle.getLeftDistance());
    Serial.print("; right = ");
    Serial.print(obstacle.getRightDistance());
    Serial.print("; front = ");
    Serial.print(obstacle.getFrontDistance());
    Serial.println();
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

