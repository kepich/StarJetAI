#pragma once
#include "GameObject.h"
class Spaceship: public GameObject{
public:
	Spaceship(double speed[2], int position[2], int type, int id): GameObject(speed, position, type, id){
		return;
	}

	bool update() {
		return true;
	}

	void render() {
		return;
	}
};

