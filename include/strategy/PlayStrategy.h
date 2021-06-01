#pragma once

#include "Strategy.h"
#include "pattern/PlayPattern.h"

class PlayStrategy: public Strategy {

	PlayPattern pattern { "play" };
	Obstacle* lastObstacle = new Obstacle(0, 0, Direction::IRELEVANT);

	bool sameObstacle(Obstacle* obstacle) {
		return abs(obstacle->getDistance() - lastObstacle->getDistance()) < 5;
	}
public:
	void init() {
	}

	void run() {
	}

	void obstacleFound(Obstacle* obstacle) {
		if (obstacle->isInRange(15)) {
			switch (W::direction) {
				case W::Movement::TURN:
				case W::Movement::BACKWARD:
					break;
				case W::Movement::STOPPED:
					actionList.removeAll();

					if (obstacle->getDirection() == Direction::FRONT_LEFT) {
						actionList.addAction(W::turnRight, 400);
					}
					if (obstacle->getDirection() == Direction::FRONT_RIGHT) {
						actionList.addAction(W::turnLeft, 400);
					}
					actionList.addAction(W::doStop, 1000);
					actionList.addAction(W::goForward, 0);
					break;
				case  W::Movement::FORWARD:
					W::doStop();
					actionList.removeAll();

					actionList.addAction(W::goBackward, 400);
					if (obstacle->getDirection() == Direction::FRONT_LEFT) {
						actionList.addAction(W::turnRight, 400);
					}
					if (obstacle->getDirection() == Direction::FRONT_RIGHT) {
						actionList.addAction(W::turnLeft, 400);
					}
					actionList.addAction(W::doStop, 1000);
					actionList.addAction(W::goForward, 0);
					break;
			}
		}
	}

} playStrategy;
