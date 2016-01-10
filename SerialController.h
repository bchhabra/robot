#include "Controller.h"


class SerialController : public Controller {
  public:
    void setup() {
      Serial.begin(9600);
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

