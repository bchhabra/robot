#pragma once

#include "Controller.h"
#include "Wheels.h"


class SerialController : public Controller {

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

public:
    void checkController() {
    	if (Serial.available()) {
    		Command cmd = getReceivedCommand();
    		switch (cmd) {
    		case FORWARD:
    			w.goForward();
    			break;
    		case BACKWARD:
    			w.goBackward();
    			break;
    		case STOP:
    			w.doStop();
    			break;
    		case LEFT:
    			w.goLeft();
    			break;
    		case RIGHT:
    			w.goRight();
    			break;
    		case LEFT_BACK:
    			w.goLeftBack();
    			break;
    		case RIGHT_BACK:
    			w.goRightBack();
    			break;
    		}
    	}
    }
};
