#pragma once

#include "SonarObstacles.h"

#define OBSTACLE_RANGE 20

class PlayStrategy {

	enum Situation {
		NO_OSTACLE_PAUSED 			= 0b00001,
		NO_OSTACLE_STOPPED 			= 0b00010,
		NO_OSTACLE_FORWARD 			= 0b00011,
		RIGHT_FRONT_OSTACLE_PAUSED 	= 0b01001,
		RIGHT_FRONT_OSTACLE_STOPPED = 0b01010,
		RIGHT_FRONT_OSTACLE_FORWARD = 0b01011,
		LEFT_FRONT_OSTACLE_PAUSED 	= 0b10001,
		LEFT_FRONT_OSTACLE_STOPPED 	= 0b10010,
		LEFT_FRONT_OSTACLE_FORWARD 	= 0b10011,
		BOTH_OSTACLES_PAUSED 		= 0b11001,
		BOTH_OSTACLES_STOPPED 		= 0b11010,
		BOTH_OSTACLES_FORWARD 		= 0b11011,
	} currentSituation;

	void assesSituation(SonarObstacles::InRange inRange) {
		currentSituation = static_cast<Situation>((inRange << 3) | (W::direction));
	}

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
		assesSituation(inRange);

		switch (currentSituation) {
			case NO_OSTACLE_PAUSED:
			case RIGHT_FRONT_OSTACLE_STOPPED:
			case LEFT_FRONT_OSTACLE_STOPPED:
			case BOTH_OSTACLES_STOPPED:
				actionList.addAction(W::goForward, 0);
				break;
			case NO_OSTACLE_STOPPED:
			case NO_OSTACLE_FORWARD:
				break;
			case RIGHT_FRONT_OSTACLE_PAUSED:
			case LEFT_FRONT_OSTACLE_PAUSED:
				actionList.removeAll();

				actionList.addAction(W::goBackward, 400);
				avoidCornerFront(inRange);
				actionList.addAction(W::doStop, 1000);
				actionList.addAction(W::goForward, 0);
				break;
			case BOTH_OSTACLES_PAUSED:
				actionList.removeAll();

				actionList.addAction(W::goBackward, 800);
				avoidCornerFront(obstacles.getClosest());
				actionList.addAction(W::doStop, 1000);
				actionList.addAction(W::goForward, 0);
				break;
			case RIGHT_FRONT_OSTACLE_FORWARD:
			case LEFT_FRONT_OSTACLE_FORWARD:
			case BOTH_OSTACLES_FORWARD:
				W::pause();
				actionList.removeAll();
				break;
		}
	}

} playStrategy;
