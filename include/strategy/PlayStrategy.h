#pragma once

#include "SonarObstacles.h"

#define OBSTACLE_RANGE 20

class PlayStrategy {

	void avoidCornerFront(SonarObstacles::Arrangement arr) {
		if (arr == SonarObstacles::LEFT_FRONT) {
			actionList.addAction(W::turnRight, 400);
		}
		if (arr == SonarObstacles::RIGHT_FRONT) {
			actionList.addAction(W::turnLeft, 400);
		}
	}
public:
	void obstacleFound(SonarObstacles& obstacles) {
		SonarObstacles::Arrangement arr = obstacles.findArrangement(OBSTACLE_RANGE);
		if (arr == SonarObstacles::NONE) return;

		switch (W::direction) {
			case W::Movement::TURN:
			case W::Movement::BACKWARD:
				break;
			case W::Movement::STOPPED:
				actionList.removeAll();

				if (arr == SonarObstacles::BOTH_FRONT) {
					avoidCornerFront(obstacles.getClosest());
				} else {
					avoidCornerFront(arr);
				}
				actionList.addAction(W::doStop, 1000);
				actionList.addAction(W::goForward, 0);
				break;
			case  W::Movement::FORWARD:
				W::doStop();
				actionList.removeAll();

				actionList.addAction(W::goBackward, 400);
				if (arr == SonarObstacles::BOTH_FRONT) {
					actionList.addAction(W::goBackward, 400);
					avoidCornerFront(obstacles.getClosest());
				} else {
					avoidCornerFront(arr);
				}
				actionList.addAction(W::doStop, 1000);
				actionList.addAction(W::goForward, 0);
				break;
		}
	}

} playStrategy;
