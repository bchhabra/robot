#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <RCSwitch.h>
#include "Wheel.h"

//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RCSwitch mySwitch = RCSwitch();

#define ENABLE 3

#define TRIGGER 12
#define ECHO 13

Wheel* left = new Wheel(8, 9);
Wheel* right = new Wheel(6, 7);

boolean running = false;
int maxRange = 200;
int minRange = 20;
long duration, distance;
int delayTurn = 500;

void setup() {
  pinMode(ENABLE, OUTPUT);

  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2

//  lcd.init();                      // initialize the lcd 
//  lcd.backlight();

//  analogWrite(ENABLE, 255);
  digitalWrite(ENABLE, HIGH);

/*
  goForward();
  delay(2000);
  goLeft();
  goRight();
*/  
  //goBackward();
  doStop();
}


void loop() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration/58.2;

  if (distance <= minRange) {
    if (running) {
      doStop();
      delay(delayTurn*2);
      goLeftBack();
    } else {
      goRightBack();
    }
  } else {
    doResume();
  }
  

  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
//    lcd.setCursor(0,1);
//    lcd.print(String(value));
    switch (value) {
      case 1361:
        running = true;
        goForward();
        break;
      case 5201:
        goLeftBack();
        break;
      case 1364: 
        running = false;
        doStop();
        break;
      case 5204: 
        goRightBack();
        break;
      case 4433: 
        goLeft();
        break;
      case 4436: 
        goRight();
        break;
    }
    mySwitch.resetAvailable();
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
  left->forward();
  right->forward();
}

void goBackward() {
  running = true;
  displayWheels("backward");
  left->backward();
  right->backward();
}

void doStop() {
  displayWheels("stopped");
  left->stop();
  right->stop();
}

void goLeft() {
  displayWheels("left");
  left->stop();
  right->forward();
  delay(delayTurn);
  doResume();
}

void goLeftBack() {
  displayWheels("left back");
  left->stop();
  right->backward();
  delay(delayTurn);
  doResume();
}

void goRight() {
  displayWheels("right");
  left->forward();
  right->stop();
  delay(delayTurn);
  doResume();
}

void goRightBack() {
  displayWheels("right back");
  left->backward();
  right->stop();
  delay(delayTurn);
  doResume();
}

void displayWheels(String direction) {
//  lcd.setCursor(0,0);
//  lcd.print(direction + "          ");
}

