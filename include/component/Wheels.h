#pragma once

#include <component/PrototypeMotor.h>
#include <component/RobotMotor.h>
#include "SerialPrinter.h"

namespace Wheels {

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

	Movement direction = Movement::STOPPED;

	void goForward() {
		printInfo("go forward");
		left.forward();
		right.forward();
		direction = Movement::FORWARD;
	}

	void goBackward() {
		printInfo("go backward");
		left.backward();
		right.backward();
		direction = Movement::BACKWARD;
	}
	
	void doStop() {
		printInfo("do stop");
		left.stop();
		right.stop();
		direction = Movement::STOPPED;
	}
	
	void pause() {
		printInfo("pause");
		left.stop();
		right.stop();
		direction = Movement::PAUSED;
	}

	void goLeft() {
		printInfo("go left");
		left.stop();
		right.forward();
		direction = Movement::TURN;
	}

	void turnLeft() {
		printInfo("turn left");
		left.backward();
		right.forward();
		direction = Movement::TURN;
	}

	void goRight() {
		printInfo("go right");
		left.forward();
		right.stop();
		direction = Movement::TURN;
	}

	void turnRight() {
		printInfo("turn right");
		left.forward();
		right.backward();
		direction = Movement::TURN;
	}

	void goLeftBack() {
		printInfo("go left back");
		left.stop();
		right.backward();
		direction = Movement::TURN;
	}

	void goRightBack() {
		printInfo("go right back");
		left.backward();
		right.stop();
		direction = Movement::TURN;
	}
}
