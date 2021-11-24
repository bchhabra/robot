#ifdef PROTOTYPE

#include "controller/Controller.h"
#include "SonarObstacles.h"
#include "component/SonarSensor.h"
#include "component/Leds.h"
#include <strategy/PlayStrategy.h>

#define SCAN_INTERVAL 35

namespace Robot {
    
    unsigned long lastScan = 0;
    SonarSensor frontLeftSensor { FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO };
    SonarSensor frontRightSensor { FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO };
    unsigned long currentTime = 0;

    void applyStrategy(SonarObstacles& obstacles);

    void setup() {
    	Leds::setup();
    }

    void loop(unsigned long currentTime) {
        if (runMode != RunMode::FULL_MANUAL && currentTime >= lastScan) {
            static byte sensorIndex = 0;
            static SonarObstacles obstacles = SonarObstacles();

            if (sensorIndex == 0) {
                obstacles.frontLeft = frontLeftSensor.scan();
                Leds::updateLeft(obstacles);
                applyStrategy(obstacles);
            } else {
                obstacles.frontRight = frontRightSensor.scan();
                Leds::updateRight(obstacles);
                applyStrategy(obstacles);
            }
            ++sensorIndex %= 2;
            lastScan = millis() + SCAN_INTERVAL;
        }
    }

    void applyStrategy(SonarObstacles& obstacles) {
        static bool secondCall = false;
        
        // first call, with only one obstacle scanned
        // second call, with both obstacles scanned
        playStrategy.obstacleFound(obstacles);
        if (secondCall) {
            obstacles.deleteObstacles();
        }
        secondCall = !secondCall;
    }

}
#endif
