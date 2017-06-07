#pragma once

#include "pattern/Pattern.h"
#include "SerialPrinter.h"

class Strategy {
protected:
	Pattern* activePattern;

	void changePattern(Pattern* pattern) {
		if (pattern && activePattern != pattern) {
			String message = "change pattern to ";
			message.concat(pattern->getName());
			serial.println(message.c_str());
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
