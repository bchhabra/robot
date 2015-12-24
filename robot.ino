#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RCSwitch.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RCSwitch mySwitch = RCSwitch();

#define LEFT 6
#define RIGHT 7

boolean running = false;

void setup() {
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2

  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  doStop();
}


void loop() {
  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
    lcd.setCursor(0,1);
    lcd.print(String(value));
    switch (value) {
      case 1361:
        goLeft();
        break;
      case 1364: 
        goRight();
        break;
      case 4433: 
        goForward();
        break;
      case 4436: 
        doStop();
        break;
    }
    mySwitch.resetAvailable();
  }
}


void goForward() {
  running = true;
  displayWheels("forward");
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, HIGH);
}

void doStop() {
  running = false;
  displayWheels("stopped");
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);
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
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
  delay(1000);
  doResume();
}

void goRight() {
  displayWheels("right");
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, HIGH);
  delay(1000);
  doResume();
}

void displayWheels(String direction) {
  lcd.setCursor(0,0);
  lcd.print(direction + "          ");
}

