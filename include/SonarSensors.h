#pragma once

#ifdef PROTOTYPE

#include <NewPing.h>

#define SCAN_INTERVAL 35

namespace SonarSensors {
    
    byte sensorIndex = 0;
    NewPing sensors[] = {NewPing(FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO), NewPing(FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO)};
    volatile bool obstacleFound = false;

    void echoCheck();

    void ping() {
        sensors[0].timer_stop();
        sensors[1].timer_stop();
        ++sensorIndex %= 2;
        sensors[sensorIndex].ping_timer(echoCheck);
    }

    void echoCheck() {
        if (sensors[sensorIndex].check_timer()) {
            obstacleFound = true;
        }
    }

    unsigned long getResult() {
        return sensors[sensorIndex].ping_result / US_ROUNDTRIP_CM;
    }
}
#endif
