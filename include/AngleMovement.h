#pragma once

#include "Action.h"
#include "imu/MinIMU9AHRS.h"

#define ANGLE_EDGE 3

class AngleMovement : public Action {
	int offset = 0;
	int targetAngle = 0;
	bool started = false;

	bool angleInBetween(int angle) {
		return (((targetAngle - ANGLE_EDGE) < angle) && (angle < (targetAngle + ANGLE_EDGE)));
	}

public:
	AngleMovement(void (*f)(), int offset) : Action(f) {
		this->offset = offset;
	}

	void playAction() override {
		targetAngle = Imu::readAngle() + offset;
		Action::playAction();
	}

	bool isFinished() override {
		return angleInBetween(Imu::readAngle());
	}
};
