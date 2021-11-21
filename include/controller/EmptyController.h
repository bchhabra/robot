#pragma once

#include <component/W.h>
#include "Controller.h"

class EmptyController: public Controller {

	Command getReceivedCommand() {
		return NONE;
	}

	bool available() {
		return false;
	}
	
};
