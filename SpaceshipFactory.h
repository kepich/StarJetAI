#pragma once
#include "Factory.h"
#include "CONF.h"
#include "AIController.h"

class SpaceshipFactory: public Factory{
public:
	static Spaceship* get_object(int controller_type, vector<GameObject*>* game_objects, double speed[2], float position[2], int id) {
		int size[2] = { SPACESHIP_WIDTH, SPACESHIP_HEIGHT };

		Controller* spaceship_controller;
		switch (controller_type){
		case AI:
			spaceship_controller = new AIController(game_objects);
			break;
		case PLAYER:
			// TODO: [add] add human controller
			spaceship_controller = NULL;
			break;
		default: 
			spaceship_controller = NULL;
			break;
		}

		return new Spaceship(spaceship_controller, speed, position, size, SPACESHIP, id);
	}
};

