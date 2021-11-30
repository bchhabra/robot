#pragma once

#ifdef PROTOTYPE

#include "SonarObstacles.h"
#include "component/SonarSensor.h"
#include "component/Leds.h"
#include "component/Wheels.h"
#include "strategy/PlayStrategy.h"

#define SCAN_INTERVAL 35

namespace Robot {
    
    unsigned long lastScan = 0;
    SonarSensor frontLeftSensor { FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO };
    SonarSensor frontRightSensor { FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO };

    byte sensorIndex = 0;
    SonarObstacles obstacles = SonarObstacles();
    NewPing sensors[] = {frontLeftSensor.getSonar(), frontRightSensor.getSonar()};
    bool obstacleFound = false;

    void applyStrategy(SonarObstacles& obstacles);
    void echoCheck();

    void ping() {
        // Serial.print("ping: ");
        // Serial.println(sensorIndex);
        sensors[sensorIndex].ping_timer(echoCheck);
    }

    void echoCheck() {
        if (sensors[sensorIndex].check_timer()) {
            // Serial.print("pong: ");
            // Serial.print(sensorIndex);
            // Serial.print(" | ping_result: ");
            // Serial.println(sensors[sensorIndex].ping_result);
            sensors[sensorIndex].timer_stop();
            if (sensorIndex == 0) {
                obstacles.frontLeft.setValues(sensors[sensorIndex].ping_result / US_ROUNDTRIP_CM, millis());
                Leds::updateLeft(obstacles);
                // Serial.print("Left: ");
                // Serial.println(obstacles.frontLeft->distance);
            } else {
                obstacles.frontRight.setValues(sensors[sensorIndex].ping_result / US_ROUNDTRIP_CM, millis());
                Leds::updateRight(obstacles);
                // Serial.print("Right: ");
                // Serial.println(obstacles.frontRight->distance);
            }
            ++sensorIndex %= 2;
            obstacleFound = true;
            lastScan = millis() + SCAN_INTERVAL;
        }
    }

    void setup() {
    	Leds::setup();
        lastScan = millis() + 1000;
    }

    void loop(unsigned long currentTime) {
        if (obstacleFound) playStrategy.obstacleFound(obstacles);
        if (runMode != RunMode::FULL_MANUAL && currentTime >= lastScan) {
            ping();
        }
    }

}
#endif
