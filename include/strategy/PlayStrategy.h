#pragma once

#include "Strategy.h"
#include "pattern/PlayPattern.h"

class PlayStrategy: public Strategy {

	PlayPattern pattern { "play" };
	Obstacle* lastObstacle = new Obstacle(0, 0);

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
				case W::Direction::TURN:
				case W::Direction::BACKWARD:
					break;
				case W::Direction::STOPPED:
					actionList.removeAll();

					actionList.addAction(W::turnRight, 400);
					actionList.addAction(W::doStop, 1000);
					actionList.addAction(W::goForward, 0);
					break;
				case  W::Direction::FORWARD:
					W::doStop();
					actionList.removeAll();

					actionList.addAction(W::goBackward, 400);
					actionList.addAction(W::turnRight, 400);
					actionList.addAction(W::doStop, 1000);
					actionList.addAction(W::goForward, 0);
					break;
			}
		}
	}

} playStrategy;
