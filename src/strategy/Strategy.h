#pragma once

#include "pattern/Pattern.h"
#include "SerialPrinter.h"

class Strategy {
protected:
	Pattern* activePattern;

	void changePattern(Pattern* pattern) {
		if (pattern && activePattern != pattern) {
			char message[200];
			strcpy(message, "change pattern to ");
			serial.println(strcat(message, pattern->getName()));
			activePattern = pattern;
			activePattern->run();
		}
	}
public:
	virtual ~Strategy(){}
	virtual void init(){}
	virtual void run() = 0;
	virtual void obstacleFound(){}
};
