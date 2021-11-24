#pragma once

#include "ActionList.h"
#include "component/W.h"

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

class Controller {
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
          actionList.addTimedAction(W::goForward, 0);
          break;
        case BACKWARD:
          actionList.addTimedAction(W::goBackward, 0);
          break;
        case STOP:
          actionList.addTimedAction(W::doStop, 0);
          break;
        case LEFT:
          actionList.addTimedAction(W::goLeft, 0);
          break;
        case RIGHT:
          actionList.addTimedAction(W::goRight, 0);
          break;
        case LEFT_BACK:
          actionList.addTimedAction(W::goLeftBack, 0);
          break;
        case RIGHT_BACK:
          actionList.addTimedAction(W::goRightBack, 0);
          break;
        case TURN_LEFT:
          actionList.addTimedAction(W::turnLeft, 0);
          break;
        case TURN_RIGHT:
          actionList.addTimedAction(W::turnRight, 0);
          break;
        default:
          break;
        }
      }
    }
};
