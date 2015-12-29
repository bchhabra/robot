#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <RCSwitch.h>

//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RCSwitch mySwitch = RCSwitch();

#define LEFT_1 8
#define LEFT_2 9
#define RIGHT_1 6
#define RIGHT_2 7
#define ENABLE 3

#define TRIGGER 12
#define ECHO 13

boolean running = false;
int maxRange = 200;
int minRange = 20;
long duration, distance;
int delayTurn = 500;

void setup() {
  pinMode(LEFT_1, OUTPUT);
  pinMode(LEFT_2, OUTPUT);
  pinMode(RIGHT_1, OUTPUT);
  pinMode(RIGHT_2, OUTPUT);
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
    doStop();
    delay(delayTurn);
    goLeftBack();
  } else {
    doResume();
  }
  

  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
//    lcd.setCursor(0,1);
//    lcd.print(String(value));
    switch (value) {
      case 1361:
        goLeft();
        break;
      case 5201:
        goLeftBack();
        break;
      case 1364: 
        goRight();
        break;
      case 5204: 
        goRightBack();
        break;
      case 4433: 
        goForward();
        break;
      case 4436: 
        running = false;
        doStop();
        break;
    }
    mySwitch.resetAvailable();
  }
}


void goForward() {
  running = true;
  displayWheels("forward");
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
}

void goBackward() {
  running = true;
  displayWheels("forward");
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
}

void doStop() {
  displayWheels("stopped");
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
}

void doResume() {
  if (running) {
    goForward();
  } else {
    doStop();
  }
}

void goLeft() {
  displayWheels("left");
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
  delay(delayTurn);
  doResume();
}

void goLeftBack() {
  displayWheels("left");
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
  delay(delayTurn);
  doResume();
}

void goRight() {
  displayWheels("right");
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  delay(delayTurn);
  doResume();
}

void goRightBack() {
  displayWheels("right");
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  delay(delayTurn);
  doResume();
}

void displayWheels(String direction) {
//  lcd.setCursor(0,0);
//  lcd.print(direction + "          ");
}

