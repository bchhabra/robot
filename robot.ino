// BOF preprocessor bug prevent - insert me on top of your arduino-code
#if 1
__asm volatile ("nop");
#endif

#define LCD 0
#define DEBUG 1

#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include "Wheels.h"
#include "SerialController.h"
#include "SonarSensor.h"
#include "Fifo.h"
#include "BoxStrategy.h"

#if LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

SerialController controller;

#define DELAY_TURN 160
Wheel leftWheel(8, 5, 9);
Wheel rightWheel(6, 7, 3);
Wheels w(&leftWheel, &rightWheel, DELAY_TURN);

BoxStrategy boxStrategy(&w);

enum Direction {
  none, forward, backward
} direction = none;

void setup() {

#if LCD
  lcd.init();
  lcd.backlight();
#endif

  Wire.begin(0x30);             // join i2c bus with address #0x30
  // deactivate internal pullups for twi.
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
  Wire.onReceive(receiveEvent); // register event

  leftWheel.setSpeed(255);
  rightWheel.setSpeed(255);
  controller.setup();
//  delay(5000);
//  direction = forward; // change this to forward if you want to move on startup
//  doResume();
}

void receiveEvent(int howMany) {
  String res = "";
  while (0 < Wire.available()) // loop through all but the last
  {
    res += (char)Wire.read(); // receive byte as a character
  }
  if (res == "f") {
    direction = forward;
    w.goForward();
  }
  if (res == "b") {
    direction = backward;
    w.goBackward();
  }
  if (res == "s") {
    direction = none;
    w.doStop();
  }
  if (res == "l") w.goLeft();
  if (res == "tl") w.turnLeft();
  if (res == "r") w.goRight();
  if (res == "tr") w.turnRight();
  if (res == "lb") w.goLeftBack();
  if (res == "rb") w.goRightBack();
}

void loop() {
  checkController();

  boxStrategy.run();
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

