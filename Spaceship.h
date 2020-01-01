#pragma once
#include "GameObject.h"
#include "Controller.h"
#include "AIController.h"

class Spaceship: public GameObject{
private:
	Controller* controller;
public:
	Spaceship(Controller* controller, double speed[2], int position[2], int size[2], int type, int id): GameObject(speed, position, size, type, id){
		this->controller = controller;
		return;
	}

	bool update() {
		return true;
	}

	void render() {
		return;
	}
};

