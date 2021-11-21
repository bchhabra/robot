#pragma once

#include "SonarObstacles.h"
#include "component/Piezzo.h"

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
			actionList.addTimedAction(W::turnRight, 400);
		}
		if (arr == SonarObstacles::RIGHT_FRONT) {
			actionList.addTimedAction(W::turnLeft, 400);
		}
	}

	void play1(SonarObstacles& obstacles, SonarObstacles::InRange inRange) {
		switch (currentSituation) {
			case NO_OSTACLE_PAUSED:
			case RIGHT_FRONT_OSTACLE_STOPPED:
			case LEFT_FRONT_OSTACLE_STOPPED:
			case BOTH_OSTACLES_STOPPED:
				Sound::stop();
				actionList.addTimedAction(W::goForward, 0)->parallel = Sound::play;
				break;
			case NO_OSTACLE_STOPPED:
			case NO_OSTACLE_FORWARD:
				break;
			case RIGHT_FRONT_OSTACLE_PAUSED:
			case LEFT_FRONT_OSTACLE_PAUSED:
				Sound::stop();
				actionList.removeAll();

				actionList.addTimedAction(W::goBackward, 400);
				avoidCornerFront(inRange);
				actionList.addTimedAction(W::pause, 1000);
				actionList.addTimedAction(W::goForward, 0)->parallel = Sound::play;
				break;
			case BOTH_OSTACLES_PAUSED:
				Sound::stop();
				actionList.removeAll();

				actionList.addTimedAction(W::goBackward, 800);
				avoidCornerFront(obstacles.getClosest());
				actionList.addTimedAction(W::pause, 1000);
				actionList.addTimedAction(W::goForward, 0)->parallel = Sound::play;
				break;
			case RIGHT_FRONT_OSTACLE_FORWARD:
			case LEFT_FRONT_OSTACLE_FORWARD:
				Sound::stop();
				W::pause();
				actionList.removeAll();
				break;
			case BOTH_OSTACLES_FORWARD:
				// this would never happen since we call this function as soon as we find one obstacle;
				// and then the robot is paused, so next call might have both obstacles but the movement is paused
				break;
		}
	}

	void play2(SonarObstacles& obstacles, SonarObstacles::InRange inRange) {
		switch (currentSituation) {
			case NO_OSTACLE_PAUSED:
			case RIGHT_FRONT_OSTACLE_STOPPED:
			case LEFT_FRONT_OSTACLE_STOPPED:
			case BOTH_OSTACLES_STOPPED:
				Sound::stop();
				actionList.addTimedAction(W::goForward, 5000)->parallel = Sound::play;	
				actionList.addTimedAction(W::turnRight, 800);
				break;
			case NO_OSTACLE_STOPPED:
			case NO_OSTACLE_FORWARD:
				break;
			case RIGHT_FRONT_OSTACLE_PAUSED:
			case LEFT_FRONT_OSTACLE_PAUSED:
				Sound::stop();
				actionList.removeAll();

				actionList.addTimedAction(W::goBackward, 400);
				avoidCornerFront(inRange);
				actionList.addTimedAction(W::pause, 1000);
				actionList.addTimedAction(W::goForward, 0)->parallel = Sound::play;
				break;
			case BOTH_OSTACLES_PAUSED:
				Sound::stop();
				actionList.removeAll();

				actionList.addTimedAction(W::goBackward, 800);
				avoidCornerFront(obstacles.getClosest());
				actionList.addTimedAction(W::pause, 1000);
				actionList.addTimedAction(W::goForward, 0)->parallel = Sound::play;
				break;
			case RIGHT_FRONT_OSTACLE_FORWARD:
			case LEFT_FRONT_OSTACLE_FORWARD:
				Sound::stop();
				W::pause();
				actionList.removeAll();
				break;
			case BOTH_OSTACLES_FORWARD:
				// this would never happen since we call this function as soon as we find one obstacle;
				// and then the robot is paused, so next call might have both obstacles but the movement is paused
				break;
		}
	}

public:
	void obstacleFound(SonarObstacles& obstacles) {
		SonarObstacles::InRange inRange = obstacles.findInRange(OBSTACLE_RANGE);
		assesSituation(inRange);

		play1(obstacles, inRange);
		// play2(obstacles, inRange);
	}

} playStrategy;
