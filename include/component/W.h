#pragma once
#include <component/Wheel.h>
#include "SerialPrinter.h"

namespace W {
	#define LEFT_FORWARD 5
	#define LEFT_BACKWARD 8
	#define RIGHT_FORWARD 7
	#define RIGHT_BACKWARD 6

	enum class Movement {
		FORWARD,
		BACKWARD,
		TURN,
		STOPPED
	};

	void printInfo(const char* message) {
		//serial.println(message);
	}

	Wheel left(LEFT_BACKWARD, LEFT_FORWARD, 9, 150);
	Wheel right(RIGHT_BACKWARD, RIGHT_FORWARD, 3, 170);

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
