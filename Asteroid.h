#pragma once
#include "GameObject.h"
class Asteroid : public GameObject{
public:
	Asteroid(double speed[2], float position[2], int size[2], int type, int id) : GameObject(speed, position, size, type, id) {
		return;
	}

	bool update() {
		this->position[0] += this->speed[0];
		this->position[1] += this->speed[1];

		return true;
	}

	void render() {
		return;
	}
};

