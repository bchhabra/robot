#pragma once

class Pattern {
public:
	virtual void init(){};
	virtual void run();
	virtual void obstacleFound();
};
