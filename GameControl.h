#pragma once
#include <vector>
#include "GameObject.h"
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"

enum UpdateStatusEnum{
	ALL_SHIPS_BROKEN,
	TIME_OUT,
	UPDATING,
	PREPARING
};

class GameControl{
private:
	Logger* log = Logger::get_logger();
	vector<GameObject*> objects = vector<GameObject*>();

	int update_status = PREPARING;
	int spaceships_count = 0;

	bool test_collision(GameObject* first, GameObject* second) {
		vector<int>* first_rect = first->get_obj_rect();
		vector<int>* second_rect = second->get_obj_rect();

		if (((*first_rect)[0] > (*second_rect)[0]) && ((*first_rect)[0] < ((*second_rect)[0] + (*second_rect)[1]))) {
			if()
		}
	}

public:
	GameControl() {
		return;
	}

	~GameControl() {
		delete log;
	}

	bool update() {
		// Updating objects
		this->update_status = UPDATING;
		log->info("GameControl updating...");

		for (GameObject* temp_object : this->objects)
			temp_object->update();

		// Deleting objects
		GameObject* deleted_object;
		for (auto temp_obj_iterator = this->objects.begin(); temp_obj_iterator < this->objects.end(); temp_obj_iterator++)
			if ((*temp_obj_iterator)->is_deleted()) {
				deleted_object = *temp_obj_iterator;
				this->objects.erase(temp_obj_iterator);
				delete deleted_object;
			}

		// Spaceships counting [Teporary] ****************
		this->spaceships_count = 0;
		for (GameObject* temp_object : this->objects)
			if (temp_object->get_type() == SPACESHIP) this->spaceships_count++;

		if (!this->spaceships_count) {
			this->update_status = ALL_SHIPS_BROKEN;
			return false;
		}
		// ***********************************************

		return true;
	}

	void render() {
		log->info("GameControl rendering...");
		return;
	}

	int get_update_status() {
		return this->update_status;
	}

	void add_object(GameObject* new_object) {
		this->objects.push_back(new_object);
	}
};

