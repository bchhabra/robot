#pragma once

#include "Pattern.h"
#include "SerialPrinter.h"

class Strategy {
protected:
	Pattern* activePattern;

	void changePattern(Pattern* pattern) {
		if (pattern && activePattern != pattern) {
			serial.println(strcat((char*)"changing pattern to ", pattern->getName()));
			activePattern = pattern;
			activePattern->run();
		}
	}
public:
	virtual void init();
	virtual void run(void (*f)());
	virtual void obstacleFound();
};
