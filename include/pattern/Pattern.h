#pragma once

class Pattern {
	const char* name;
public:
	Pattern(const char* name) {
		this->name = name;
	}
	virtual ~Pattern(){}
	const char* getName() {
		return name;
	}
	virtual void init(){}
	virtual void run() = 0;
	virtual void obstacleFound(unsigned long interruptTime){}
};
