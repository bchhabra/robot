#pragma once

#include <Arduino.h>
#include "DelegateAction.h"
#include "imu/MinIMU9AHRS.h"

class AngleMovement : public DelegateAction {
	int offset = 0;
	int targetAngle = 0;
	bool started = false;

public:
	AngleMovement(void (*f)(), int offset) : DelegateAction(f) {
		this->offset = offset;
	}

	void playAction() {
		targetAngle = (Imu::readAngle() + offset + 360) % 360;
		DelegateAction::playAction();
		started = true;
	}

	bool isFinished() {
		return Imu::readAngle() == targetAngle;
	}

	bool isStarted() {
		return started;
	}
};
