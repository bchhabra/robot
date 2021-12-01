#pragma once

#ifdef PROTOTYPE

#include "SonarSensors.h"
#include "component/Leds.h"
#include "strategy/PlayStrategy.h"

namespace Robot {
    
    unsigned long lastScan = 0;

    SonarObstacles obstacles = SonarObstacles();

    void setup() {
    	Leds::setup();
        lastScan = millis() + 1000;
    }

    void loop(unsigned long currentTime) {
        if (SonarSensors::obstacleFound) {
            SonarSensors::obstacleFound = false;
            if (SonarSensors::sensorIndex == 0) {
                obstacles.frontLeft.setValues(SonarSensors::getResult(), currentTime);
                Leds::updateLeft(obstacles);
            } else {
                obstacles.frontRight.setValues(SonarSensors::getResult(), currentTime);
                Leds::updateRight(obstacles);
            }
            playStrategy.obstacleFound(obstacles);
        }
        if (runMode != RunMode::FULL_MANUAL && currentTime >= lastScan) {
            lastScan = currentTime + SCAN_INTERVAL;
            SonarSensors::ping();
        }
    }

}
#endif
