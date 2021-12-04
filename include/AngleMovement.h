#pragma once

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

	void playAction() override {
		targetAngle = Imu::readAngle() + offset;
		Action::playAction();
		started = true;
	}

	bool isFinished() override {
		return (Imu::readAngle() == targetAngle);
	}

	bool isStarted() override {
		return started;
	}
};
