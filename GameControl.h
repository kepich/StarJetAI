#pragma once
#include <vector>
#include "GameObject.h"
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"

class GameControl{
private:
	Logger* log = Logger::get_logger();
	vector<GameObject*> objects = vector<GameObject*>();

public:
	GameControl() {
		return;
	}

	bool update() {
		// Updating objects
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

		log->info("GameControl updating...");
		return true;
	}

	void render() {
		log->info("GameControl rendering...");
		return;
	}
};

