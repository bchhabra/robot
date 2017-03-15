#pragma once

class Pattern {
	const char* name;
public:
	Pattern(const char* name) {
		this->name = name;
	}
	const char* getName() {
		return name;
	}
	virtual void init(){};
	virtual void run();
	virtual void obstacleFound();
};
