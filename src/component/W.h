#pragma once

#include <component/Wheel.h>
#include "SerialPrinter.h"

#define LEFT_FORWARD 5
#define LEFT_BACKWARD 8
#define RIGHT_FORWARD 7
#define RIGHT_BACKWARD 6

Wheel left(LEFT_BACKWARD, LEFT_FORWARD, 9);
Wheel right(RIGHT_BACKWARD, RIGHT_FORWARD, 3);

class W {
	static void printInfo(const char* message) {
		serial.println(message);
	}

public:
	static void goForward() {
		printInfo("go forward");
		left.forward();
		right.forward();
	}

	static void goBackward() {
		printInfo("go backward");
		left.backward();
		right.backward();
	}
	
	static void doStop() {
		printInfo("do stop");
		left.stop();
		right.stop();
	}

	static void goLeft() {
		printInfo("go left");
		left.stop();
		right.forward();
	}

	static void turnLeft() {
		printInfo("turn left");
		left.backward();
		right.forward();
	}

	static void goRight() {
		printInfo("go right");
		left.forward();
		right.stop();
	}

	static void turnRight() {
		printInfo("turn right");
		left.forward();
		right.backward();
	}

	static void goLeftBack() {
		printInfo("go left back");
		left.stop();
		right.backward();
	}

	static void goRightBack() {
		printInfo("go right back");
		left.backward();
		right.stop();
	}

};
