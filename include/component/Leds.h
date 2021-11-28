#pragma once

#include <Arduino.h>
#include "Pins.h"
#include "SonarObstacles.h"

namespace Leds {
    void allOn();
    void allOff();

    void setup() {
#if LEDS
        pinMode(PIN_LEFT_FAR, OUTPUT);
        pinMode(PIN_LEFT_CLOSE, OUTPUT);
        pinMode(PIN_RIGHT_FAR, OUTPUT);
        pinMode(PIN_RIGHT_CLOSE, OUTPUT);
        allOn();
        delay(500);
        allOff();
#endif
    }

#if LEDS
    void update(SonarObstacle& obstacle, uint8_t pinClose, uint8_t pinFar) {
        if (obstacle.isInRange(OBSTACLE_RANGE)) {
            digitalWrite(pinClose, HIGH);
            digitalWrite(pinFar, HIGH);
        } else if (obstacle.isInRange(MAX_DISTANCE)) {
            digitalWrite(pinClose, LOW);
            digitalWrite(pinFar, HIGH);
        } else {
            digitalWrite(pinClose, LOW);
            digitalWrite(pinFar, LOW);
        }
    }
#endif

    void updateLeft(SonarObstacles& obstacles) {
#if LEDS
        update(obstacles.frontLeft, PIN_LEFT_CLOSE, PIN_LEFT_FAR);
#endif
    }

    void updateRight(SonarObstacles& obstacles) {
#if LEDS
        update(obstacles.frontRight, PIN_RIGHT_CLOSE, PIN_RIGHT_FAR);
#endif
    }

    void allOn() {
#if LEDS
        digitalWrite(PIN_LEFT_FAR, HIGH);
        digitalWrite(PIN_LEFT_CLOSE, HIGH);
        digitalWrite(PIN_RIGHT_FAR, HIGH);
        digitalWrite(PIN_RIGHT_CLOSE, HIGH);
#endif
    }

    void allOff() {
#if LEDS
        digitalWrite(PIN_LEFT_FAR, LOW);
        digitalWrite(PIN_LEFT_CLOSE, LOW);
        digitalWrite(PIN_RIGHT_FAR, LOW);
        digitalWrite(PIN_RIGHT_CLOSE, LOW);
#endif
    }
}
