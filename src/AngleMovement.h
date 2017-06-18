#pragma once

#include <Arduino.h>
#include "Action.h"
#include "imu/MinIMU9AHRS.h"

class AngleMovement : public Action {
	int angle = 0;
	int startAngle = 0;
	bool started = false;

public:
	AngleMovement(void (*f)(), int angle) : Action(f) {
		this->angle = angle;
	}

	void playAction() {
		startAngle = readAngle();
		action();
		started = true;
	}

	bool isFinished() {
		return (calculateDelta(readAngle(), startAngle) >= angle);
	}

	bool isStarted() {
		return started;
	}
};
