#include "Controller.h"
#include <Wire.h>

typedef void (*callback)(Command);
callback f;

void receiveEvent(int howMany) {
  String res = "";
  while (0 < Wire.available()) // loop through all but the last
  {
    res += (char)Wire.read(); // receive byte as a character
  }
  if (res == "f") f(FORWARD);
  if (res == "b") f(BACKWARD);
  if (res == "s") f(STOP);
  if (res == "l") f(LEFT);
  if (res == "tl") f(TURN_LEFT);
  if (res == "r") f(RIGHT);
  if (res == "tr") f(TURN_RIGHT);
  if (res == "lb") f(LEFT_BACK);
  if (res == "rb") f(RIGHT_BACK);
}

class WiFiController : public Controller {
  private:
  
  
  public:
    WiFiController(callback func) {
      f = func;
    }
  
    void setup() {
      Wire.begin(0x30);                // join i2c bus with address #0x30
      Wire.onReceive(receiveEvent); // register event
    }

    boolean available() {
      return Serial.available();
    }

    Command getReceivedCommand() {
      String value = Serial.readStringUntil('\n');
      if (value == "f") return FORWARD;
      if (value == "b") return BACKWARD;
      if (value == "s") return STOP;
      if (value == "l") return LEFT;
      if (value == "r") return RIGHT;
      if (value == "lb") return LEFT_BACK;
      if (value == "rb") return RIGHT_BACK;
    }
};

