#pragma once
#include <component/Wheel.h>
#include "SerialPrinter.h"

namespace W {
	#define LEFT_FORWARD 5
	#define LEFT_BACKWARD 8
	#define RIGHT_FORWARD 7
	#define RIGHT_BACKWARD 6

	enum class Direction {
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

	Direction direction = Direction::STOPPED;

	void goForward() {
		printInfo("go forward");
		left.forward();
		right.forward();
		W::direction = Direction::FORWARD;
	}

	static void goBackward() {
		printInfo("go backward");
		left.backward();
		right.backward();
		direction = Direction::BACKWARD;
	}
	
	static void doStop() {
		printInfo("do stop");
		left.stop();
		right.stop();
		direction = Direction::STOPPED;
	}

	static void goLeft() {
		printInfo("go left");
		left.stop();
		right.forward();
		direction = Direction::TURN;
	}

	static void turnLeft() {
		printInfo("turn left");
		left.backward();
		right.forward();
		direction = Direction::TURN;
	}

	static void goRight() {
		printInfo("go right");
		left.forward();
		right.stop();
		direction = Direction::TURN;
	}

	static void turnRight() {
		printInfo("turn right");
		left.forward();
		right.backward();
		direction = Direction::TURN;
	}

	static void goLeftBack() {
		printInfo("go left back");
		left.stop();
		right.backward();
		direction = Direction::TURN;
	}

	static void goRightBack() {
		printInfo("go right back");
		left.backward();
		right.stop();
		direction = Direction::TURN;
	}
}
