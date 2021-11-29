#pragma once

#if CONTROLLER
#else

#include <component/Wheels.h>
#include "Controller.h"

class EmptyController: public Controller {

	Command getReceivedCommand() override {
		return NONE;
	}

	bool available() override {
		return false;
	}
	
} controller;
#endif