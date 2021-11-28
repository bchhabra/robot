#ifdef PROTOTYPE

#include "controller/Controller.h"
#include "SonarObstacles.h"
#include "component/SonarSensor.h"
#include "component/Leds.h"
#include <strategy/PlayStrategy.h>

#define SCAN_INTERVAL 35

namespace Robot {
    
    SonarSensor frontLeftSensor { FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO };
    SonarSensor frontRightSensor { FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO };

    void applyStrategy(SonarObstacles& obstacles);

    void setup() {
    	Leds::setup();
    }

    void loop(unsigned long currentTime) {
        static unsigned long lastScan = 0;
        if (runMode != RunMode::FULL_MANUAL && currentTime >= lastScan) {
            static byte sensorIndex = 0;
            static SonarObstacles obstacles = SonarObstacles();

            if (sensorIndex == 0) {
                frontLeftSensor.scan(obstacles.frontLeft);
                Leds::updateLeft(obstacles);
                playStrategy.obstacleFound(obstacles);
            } else {
                frontRightSensor.scan(obstacles.frontRight);
                Leds::updateRight(obstacles);
                playStrategy.obstacleFound(obstacles);
            }
            ++sensorIndex %= 2;
            lastScan = millis() + SCAN_INTERVAL;
        }
    }

}
#endif
