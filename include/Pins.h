#pragma once

#include <pins_arduino.h>

#ifdef PROTOTYPE

    #define LEFT_WHEEL_FORWARD 5
    #define LEFT_WHEEL_BACKWARD 8
    #define LEFT_WHEEL_SPEED 9

    #define RIGHT_WHEEL_FORWARD 7
    #define RIGHT_WHEEL_BACKWARD 6
    #define RIGHT_WHEEL_SPEED 10

#ifdef LEDS
    #define PIN_LEFT_FAR A3
    #define PIN_LEFT_CLOSE A2
    #define PIN_RIGHT_FAR A1
    #define PIN_RIGHT_CLOSE A0
#endif

#if SOUND
    #define PIEZZO_PIN 3
#endif

#if CONTROLLER & CTRL_BLUE
    #define BLUE_STATE_PIN 11
#endif

    #define FRONT_LEFT_SONAR_TRIGGER 13
    #define FRONT_LEFT_SONAR_ECHO 2
    #define FRONT_RIGHT_SONAR_TRIGGER 4
    #define FRONT_RIGHT_SONAR_ECHO 12

#else

    #define LEFT_WHEEL_FORWARD 5
    #define LEFT_WHEEL_BACKWARD 8
    #define LEFT_WHEEL_SPEED 9 // not used but compilation fails - requires some code changes

    #define RIGHT_WHEEL_FORWARD 7
    #define RIGHT_WHEEL_BACKWARD 6
    #define RIGHT_WHEEL_SPEED 10 // not used but compilation fails - requires some code changes

    #define PORT_CONTACTSENSORS 2

#endif
