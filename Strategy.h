#pragma once

#include "Pattern.h"

class Strategy {
protected:
	Pattern* activePattern;

	void changePattern(Pattern* pattern) {
		if (pattern && activePattern != pattern) {
			activePattern = pattern;
			activePattern->run();
		}
	}
public:
	void init();
	void run(void (*f)());
	void obstacleFound();
};
