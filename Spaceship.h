#pragma once
#include "GameObject.h"
#include "Controller.h"
#include "AIController.h"

class Spaceship: public GameObject{
private:
	Controller* controller;

	void add_force(double x_axis, double y_axis) {
		this->speed[0] += x_axis;
		this->speed[1] += y_axis;
	}

public:
	Spaceship(Controller* controller, double speed[2], float position[2], int size[2], int type, int id): GameObject(speed, position, size, type, id){
		this->controller = controller;
		return;
	}

	bool update() {
		pair<double, double> speed = this->controller->get_move();

		this->position[0] += int(speed.first);
		this->position[1] += int(speed.second);
		return true;
	}

	void render() {
		return;
	}
};

