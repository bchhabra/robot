#ifndef PROTOTYPE

#include "component/Wheels.h"
#include <strategy/FactoryStrategy.h>

namespace Robot {

    volatile bool interruptCalled = false;

    IRAM_ATTR void interrupt() {
        interruptCalled = true;
    }
    
    void setup() {
        attachInterrupt(digitalPinToInterrupt(PORT_CONTACTSENSORS), interrupt, FALLING);
        changeStrategy(&factoryStrategy);
    }

    void loop(unsigned long currentTime) {
        if (interruptCalled) {
            interruptCalled = false;
            Obstacle* obstacle = new Obstacle(currentTime);
            activeStrategy->obstacleFound(obstacle);
            delete obstacle;
        } else {
            activeStrategy->run();
        }
    }
}
#endif
