#pragma once
#include "Controller.h"
#include "CONF.h"

class AIController : public Controller{
private:

public:
	pair<double, double> get_move() {
		return pair<int, int>(1, 1);
	}
};

