#pragma once

#include "Controller.h"
#include <Wire.h>

class WiFiController : public Controller {

  typedef void (*callback)(Command);
  callback f;  
  
  public:
    static void receiveEvent(int howMany) {
      String res = "";
      while (0 < Wire.available()) // loop through all but the last
      {
        res += (char)Wire.read(); // receive byte as a character
      }
      if (res == "f") wifiController.f(FORWARD);
      if (res == "b") wifiController.f(BACKWARD);
      if (res == "s") wifiController.f(STOP);
      if (res == "l") wifiController.f(LEFT);
      if (res == "tl") wifiController.f(TURN_LEFT);
      if (res == "r") wifiController.f(RIGHT);
      if (res == "tr") wifiController.f(TURN_RIGHT);
      if (res == "lb") wifiController.f(LEFT_BACK);
      if (res == "rb") wifiController.f(RIGHT_BACK);
    }
    
    WiFiController(callback func) {
      f = func;
    }
  
    void setup() override {
      Wire.begin(0x30);                // join i2c bus with address #0x30
      Wire.onReceive(receiveEvent); // register event
    }

    bool available() override {
      return Serial.available();
    }

    Command getReceivedCommand() override {
      String value = Serial.readStringUntil('\n');
      if (value == "f") return FORWARD;
      if (value == "b") return BACKWARD;
      if (value == "s") return STOP;
      if (value == "l") return LEFT;
      if (value == "r") return RIGHT;
      if (value == "lb") return LEFT_BACK;
      if (value == "rb") return RIGHT_BACK;
    }
} wifiController;
