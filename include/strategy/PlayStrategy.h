#pragma once

#include "SonarObstacles.h"

#define OBSTACLE_RANGE 20

class PlayStrategy {

	void avoidCornerFront(SonarObstacles::InRange arr) {
		if (arr == SonarObstacles::LEFT_FRONT) {
			actionList.addAction(W::turnRight, 400);
		}
		if (arr == SonarObstacles::RIGHT_FRONT) {
			actionList.addAction(W::turnLeft, 400);
		}
	}
public:
	void obstacleFound(SonarObstacles& obstacles) {
		SonarObstacles::InRange inRange = obstacles.findInRange(OBSTACLE_RANGE);
		if (inRange == SonarObstacles::NONE) {
			if (W::direction == W::Movement::STOPPED) {
				actionList.addAction(W::goForward, 0);
			}
			return;
		}

		switch (W::direction) {
			case W::Movement::TURN:
			case W::Movement::BACKWARD:
				break;
			case W::Movement::STOPPED:
				actionList.removeAll();

				actionList.addAction(W::goBackward, 400);
				if (inRange == SonarObstacles::BOTH_FRONT) {
					actionList.addAction(W::goBackward, 400);
					avoidCornerFront(obstacles.getClosest());
				} else {
					avoidCornerFront(inRange);
				}
				actionList.addAction(W::doStop, 1000);
				actionList.addAction(W::goForward, 0);
				break;
			case  W::Movement::FORWARD:
				W::doStop();
				actionList.removeAll();
				break;
		}
	}

} playStrategy;
