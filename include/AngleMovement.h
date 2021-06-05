#pragma once

#include <Arduino.h>
#include "Action.h"
#include "imu/MinIMU9AHRS.h"

class AngleMovement : public Action {
	int offset = 0;
	int targetAngle = 0;
	bool started = false;

public:
	AngleMovement(void (*f)(), int offset) : Action(f) {
		this->offset = offset;
	}

	void playAction() {
		targetAngle = (Imu::readAngle() + offset + 360) % 360;
		action();
		started = true;
	}

	bool isFinished() {
		return Imu::readAngle() == targetAngle;
	}

	bool isStarted() {
		return started;
	}
};
