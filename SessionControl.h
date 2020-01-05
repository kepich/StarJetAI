#pragma once
#include <vector>
#include "GameObject.h"
#include "utils.h"

using namespace std;

class SessionControl{
private:
	vector<GameObject*>* objects;
	int spaceships_count;

	void initialisation() {
		float* speed = new float[2];
		speed[0] = DEFAULT_SPEED_X;
		speed[1] = DEFAULT_SPEED_Y;

		float* position = new float[2];
		position[0] = DEFAULT_POSITION_X;
		position[1] = DEFAULT_POSITION_Y;

		this->add_object(SpaceshipFactory::get_object(AI, this->objects, speed, position, this->objects->size()));
		this->add_object(AsteroidFactory::get_object(speed[0], speed[1], speed, position, this->objects->size()));

		delete[] speed;
		delete[] position;
	}


	void add_object(GameObject* new_object) {
		this->objects->push_back(new_object);
	}

public:
	SessionControl(vector<GameObject*>* objects) {
		this->objects = objects;
		spaceships_count = 0;
	}

	int update() {
		if (!this->objects->size()) {
			initialisation();
		}

		// Deleting objects
		GameObject* deleted_object;
		for (auto temp_obj_iterator = this->objects->begin(); temp_obj_iterator < this->objects->end(); temp_obj_iterator++)
			if ((*temp_obj_iterator)->is_deleted()) {
				deleted_object = *temp_obj_iterator;
				this->objects->erase(temp_obj_iterator);
				delete deleted_object;
			}

		// Spaceships counting [Teporary] ****************
		this->spaceships_count = 0;
		for (GameObject* temp_object : *(this->objects))
			if (temp_object->get_type() == SPACESHIP) this->spaceships_count++;


		if (!this->spaceships_count)
			return ALL_SHIPS_BROKEN;

		// ***********************************************
		return UPDATING;
	}
};

