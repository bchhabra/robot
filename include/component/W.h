#pragma once
#include <component/Wheel.h>
#include "SerialPrinter.h"
#include "Pins.h"

namespace W {

	enum Movement {
		PAUSED 		= 0b001,
		STOPPED 	= 0b010,
		FORWARD 	= 0b011,
		BACKWARD 	= 0b100,
		TURN 		= 0b101,
	};

	void printInfo(const char* message) {
		serial.println(message);
	}

	Wheel left(LEFT_WHEEL_BACKWARD, LEFT_WHEEL_FORWARD, LEFT_WHEEL_SPEED, 150);
	Wheel right(RIGHT_WHEEL_BACKWARD, RIGHT_WHEEL_FORWARD, RIGHT_WHEEL_SPEED, 180);

	Movement direction = Movement::STOPPED;

	void goForward() {
		printInfo("go forward");
		left.forward();
		right.forward();
		W::direction = Movement::FORWARD;
	}

	static void goBackward() {
		printInfo("go backward");
		left.backward();
		right.backward();
		direction = Movement::BACKWARD;
	}
	
	static void doStop() {
		printInfo("do stop");
		left.stop();
		right.stop();
		direction = Movement::STOPPED;
	}
	
	static void pause() {
		printInfo("pause");
		left.stop();
		right.stop();
		direction = Movement::PAUSED;
	}

	static void goLeft() {
		printInfo("go left");
		left.stop();
		right.forward();
		direction = Movement::TURN;
	}

	static void turnLeft() {
		printInfo("turn left");
		left.backward();
		right.forward();
		direction = Movement::TURN;
	}

	static void goRight() {
		printInfo("go right");
		left.forward();
		right.stop();
		direction = Movement::TURN;
	}

	static void turnRight() {
		printInfo("turn right");
		left.forward();
		right.backward();
		direction = Movement::TURN;
	}

	static void goLeftBack() {
		printInfo("go left back");
		left.stop();
		right.backward();
		direction = Movement::TURN;
	}

	static void goRightBack() {
		printInfo("go right back");
		left.backward();
		right.stop();
		direction = Movement::TURN;
	}
}
