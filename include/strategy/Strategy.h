#pragma once

#include "pattern/Pattern.h"
#include "SerialPrinter.h"
#include "Obstacle.h"

class Strategy {
protected:
	Pattern* activePattern;

	void changePattern(Pattern* pattern) {
		if (pattern && activePattern != pattern) {
			String message = "change pattern to ";
			message.concat(pattern->getName());
			serial.println(message.c_str());
			activePattern = pattern;
		}
	}
public:
	virtual ~Strategy(){}
	virtual void init(){}
	virtual void run() = 0;
	virtual void obstacleFound(Obstacle* obstacle){}

	bool activePatternIs(Pattern* pattern) {
		return activePattern == pattern;
	}
};

Strategy* activeStrategy;
Strategy* previousStrategy;

void changeStrategy(Strategy* strategy) {
	if (strategy && strategy != activeStrategy) {
		previousStrategy = activeStrategy;
		activeStrategy = strategy;
		activeStrategy->init();
	}
}
