#pragma once

#include <component/W.h>
#include "Controller.h"

class EmptyController: public Controller {

	Command getReceivedCommand() override {
		return NONE;
	}

	bool available() override {
		return false;
	}
	
};
