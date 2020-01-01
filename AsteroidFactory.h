#pragma once
#include "Asteroid.h"
#include "Factory.h"

class AsteroidFactory : public Factory {
public:
	static Asteroid* get_object(int _asteroid_width, int _asteroid_height,double speed[2], int position[2], int id) {
		int size[2] = { _asteroid_width, _asteroid_height };
		return new Asteroid(speed, position, size, SPACESHIP, id);
	}
};

