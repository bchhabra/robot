#pragma once

enum Command {
  FORWARD,
  BACKWARD,
  STOP,
  LEFT,
  TURN_LEFT,
  RIGHT,
  TURN_RIGHT,
  LEFT_BACK,
  RIGHT_BACK
};

class Controller {
  public:
    void setup();
    boolean available();
    Command getReceivedCommand();
};

