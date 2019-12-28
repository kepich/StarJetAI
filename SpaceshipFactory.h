#pragma once
#include "Factory.h"
#include "Spaceship.h"

class SpaceshipFactory: public Factory{
public:
	static Spaceship* get_object(double speed[2], int position[2], int id) {
		return new Spaceship(speed, position, SPACESHIP, id);
	}
};

