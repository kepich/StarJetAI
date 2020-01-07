#pragma once
#include "GameObject.h"
#include "utils.h"
#include "Logger.h"
#include "AsteroidFactory.h"
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

class SessionControl{
private:
	vector<GameObject*>* objects;
	int number_of_spaceships_in_game = 0;
	int number_of_asteroids_in_game = 0;
	int number_of_passed_asteroids = 0;
	int temp_asteroid = 0;
	vector<GameObject*> asteroids;
	queue<GameObject*> deleted_spaceships_queue;

	Logger* log;

	void initialisation() {
		
		//  Create population of spaceships
		//	Fill asteroids queue
		ifstream asteroids_file("asteroids_info", ios::in);

		if (asteroids_file.is_open()) {
			asteroids_file >> this->number_of_passed_asteroids;
			int t_width, t_height;
			float t_speed[2], t_pos[2];
			GameObject* t_obj;

			for (int i = 0; i < this->number_of_passed_asteroids; i++) {
				asteroids_file >> t_width >> t_height >> t_speed[0] >> t_speed[1] >> t_pos[0] >> t_pos[1];
				t_obj = AsteroidFactory::get_object(t_width, t_height, t_speed, t_pos, this->objects->size());
				this->objects->push_back(t_obj);
				this->asteroids.push_back(t_obj);
			}

			this->number_of_passed_asteroids = this->asteroids.size();
		}
		else {
			log->error("Cannot open asteroids file");
			exit(-1);
		}
	}


	void add_object(GameObject* new_object) {
		this->objects->push_back(new_object);
	}

	int add_asteroid_from_queue() {
		if (!this->asteroids.size())
			return LEARNING_COMPLETE;
		
		this->objects->push_back(this->asteroids[this->temp_asteroid++]);

		return UPDATING;
	}

public:
	SessionControl(vector<GameObject*>* objects) {
		this->objects = objects;
		this->number_of_spaceships_in_game = 0;
		this->number_of_asteroids_in_game = 0;
		this->number_of_passed_asteroids = 0;

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
		this->number_of_spaceships_in_game = 0;
		this->number_of_asteroids_in_game = 0;

		for (GameObject* temp_object : *(this->objects))
			if (temp_object->get_type() == SPACESHIP) this->number_of_spaceships_in_game++;
			else if (temp_object->get_type() == ASTEROID) this->number_of_asteroids_in_game++;


		if (!this->number_of_spaceships_in_game) {
			this->temp_asteroid = 0;
			return ALL_SHIPS_BROKEN;
		}
		if (!this->number_of_asteroids_in_game)
			return this->add_asteroid_from_queue();


		// ***********************************************
		return UPDATING;
	}

	void evaluate() {

	}
};

