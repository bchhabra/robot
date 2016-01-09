#include <RCSwitch.h>
#include "Controller.h"


class RfController : public Controller {
    RCSwitch mySwitch = RCSwitch();
  public:
    void setup() {
      mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2        
    }

    boolean available() {
      return mySwitch.available();
    }

    Command getReceivedCommand() {
      unsigned long value = mySwitch.getReceivedValue();
      mySwitch.resetAvailable();
      switch (value) {
        case 1361:
          return FORWARD;
        case 5201:
          return LEFT_BACK;
        case 1364: 
          return STOP;
        case 5204: 
          return RIGHT_BACK;
        case 4433: 
          return LEFT;
        case 4436: 
          return RIGHT;
      }
    }
};

