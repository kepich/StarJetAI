#pragma once
#include "GameObject.h"
#include "utils.h"
#include "Logger.h"
#include <queue>
#include <vector>

using namespace std;

class SessionControl{
private:
	vector<GameObject*>* objects;
	int spaceships_count = 0;
	int asteroids_count = 0;
	int asteroid_fit_count = 0;
	queue<GameObject*> asteroid_queue;
	queue<GameObject*> deleted_spaceships_queue;

	Logger* log;

	void initialisation() {
		
		//  Create population of spaceships
		//	Fill asteroids queue


		this->asteroid_fit_count = this->asteroid_queue.size();
	}


	void add_object(GameObject* new_object) {
		this->objects->push_back(new_object);
	}

	int add_asteroid_from_queue() {
		if (!this->asteroid_queue.size())
			return LEARNING_COMPLETE;
		
		this->objects->push_back(this->asteroid_queue.front());
		this->asteroid_queue.pop();

		return UPDATING;
	}

public:
	SessionControl(vector<GameObject*>* objects) {
		this->objects = objects;
		this->spaceships_count = 0;
		this->asteroids_count = 0;
		this->asteroid_fit_count = 0;

		this->log = new Logger("SessionControl.log");
	}

	int update() {
		if (!this->objects->size()) {
			initialisation();
		}

		// Deleting objects
		for (auto temp_obj_iterator = this->objects->begin(); temp_obj_iterator < this->objects->end(); temp_obj_iterator++)
			if ((*temp_obj_iterator)->is_deleted()) {
				this->deleted_spaceships_queue.push(*temp_obj_iterator);
				this->objects->erase(temp_obj_iterator);
			}

		// Objects counting ***************************
		this->spaceships_count = 0;
		this->asteroids_count = 0;

		for (GameObject* temp_object : *(this->objects))
			if (temp_object->get_type() == SPACESHIP) this->spaceships_count++;
			else if (temp_object->get_type() == ASTEROID) this->asteroids_count++;


		if (!this->spaceships_count)
			return ALL_SHIPS_BROKEN;
		if (!this->asteroids_count)
			return this->add_asteroid_from_queue();


		// ***********************************************
		return UPDATING;
	}

	void evaluate() {

	}
};

