#pragma once

using namespace std;

class Controller{
private:
	int controller_type = EMPTY;
public:
	Controller(int controller_type) {
		this->controller_type = controller_type;
	}

	int get_type() {
		return this->controller_type;
	}

	virtual pair<float, float> get_move() = 0;
};

