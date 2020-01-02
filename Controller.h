#pragma once

using namespace std;

class Controller{
public:
	virtual pair<double, double> get_move() = 0;
};

