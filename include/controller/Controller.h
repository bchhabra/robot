#pragma once

#include "ActionList.h"
#include "component/W.h"

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
          W::goForward();
          break;
        case BACKWARD:
          W::goBackward();
          break;
        case STOP:
          W::doStop();
          break;
        case LEFT:
          W::goLeft();
          break;
        case RIGHT:
          W::goRight();
          break;
        case LEFT_BACK:
          W::goLeftBack();
          break;
        case RIGHT_BACK:
          W::goRightBack();
          break;
        case TURN_LEFT:
          W::turnLeft();
          break;
        case TURN_RIGHT:
          W::turnRight();
          break;
        default:
          break;
        }
      }
    }
};
