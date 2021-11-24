#pragma once

#include <component/Leds.h>

enum RunMode {
    FULL_MANUAL,
    MANUAL_WITH_SENSORS,
    AUTO
} runMode;

namespace Run {

    void setMode(RunMode mode) {
        runMode = mode;
        switch (runMode) {
        case RunMode::AUTO:
        case RunMode::MANUAL_WITH_SENSORS:
            break;
        case RunMode::FULL_MANUAL:
            actionList.removeAll();
            W::doStop();
            Leds::allOff();
            break;
        }
    }

    void toggleSensors() {
        setMode(static_cast<RunMode>(!(runMode & 0x1)));
    }
}
