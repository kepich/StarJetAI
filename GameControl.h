#pragma once
#include <vector>
#include "GameObject.h"
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"
#include "Asteroid.h"
#include "AsteroidFactory.h"

enum UpdateStatusEnum{
	ALL_SHIPS_BROKEN,
	TIME_OUT,
	UPDATING,
	PREPARING
};

class GameControl{
private:
	Logger* log = Logger::get_logger();
	vector<GameObject*>* objects = new vector<GameObject*>();

	int update_status = PREPARING;
	int spaceships_count = 0;

	static bool test_x_collision(vector<float>* first_rect, vector<float>* second_rect) {
		if (((*first_rect)[0] > (*second_rect)[0]) && ((*first_rect)[0] < ((*second_rect)[0] + (*second_rect)[1])))
			return true;
		else if ((((*first_rect)[0] + (*first_rect)[1]) > (*second_rect)[0]) && (((*first_rect)[0] + (*first_rect)[1]) < ((*second_rect)[0] + (*second_rect)[1])))
			return true;
		else
			return false;
	};

	static bool test_y_collision(vector<float>* first_rect, vector<float>* second_rect) {
		if (((*first_rect)[2] > (*second_rect)[2]) && ((*first_rect)[2] < ((*second_rect)[2] + (*second_rect)[3])))
			return true;
		else if ((((*first_rect)[2] + (*first_rect)[2]) > (*second_rect)[2]) && (((*first_rect)[2] + (*first_rect)[3]) < ((*second_rect)[2] + (*second_rect)[3])))
			return true;
		else
			return false;
	};

	static bool test_collision(GameObject* first, GameObject* second) {
		vector<float>* first_rect = first->get_obj_rect();
		vector<float>* second_rect = second->get_obj_rect();

		return ((GameControl::test_x_collision(first_rect, second_rect) ||
			GameControl::test_x_collision(second_rect, first_rect)) &&
			(GameControl::test_y_collision(first_rect, second_rect) ||
				GameControl::test_y_collision(second_rect, first_rect)));
	}

public:
	GameControl() {
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
		
		return;
	}

	~GameControl() {
		delete log;
	}

	bool update() {
		// Updating objects
		this->update_status = UPDATING;
		log->info("GameControl updating...");

		for (GameObject* temp_object : *(this->objects))
			temp_object->update();

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
		this->objects->push_back(new_object);
	}
};

