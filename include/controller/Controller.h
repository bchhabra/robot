#pragma once

#include "ActionList.h"
#include "component/Wheels.h"

class Controller {

  protected:
    enum Command {
      NONE,
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

    virtual bool available();
    virtual Command getReceivedCommand();

  public:
    virtual void setup() {}

    void checkController() {
      if (available()) {
        actionList.removeAll();
        Command cmd = getReceivedCommand();
        switch (cmd) {
        case FORWARD:
          Wheels::goForward();
          break;
        case BACKWARD:
          Wheels::goBackward();
          break;
        case STOP:
          Wheels::doStop();
          break;
        case LEFT:
          Wheels::goLeft();
          break;
        case RIGHT:
          Wheels::goRight();
          break;
        case LEFT_BACK:
          Wheels::goLeftBack();
          break;
        case RIGHT_BACK:
          Wheels::goRightBack();
          break;
        case TURN_LEFT:
          Wheels::turnLeft();
          break;
        case TURN_RIGHT:
          Wheels::turnRight();
          break;
        default:
          break;
        }
      }
    }
};
