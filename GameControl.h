#pragma once
#include <vector>
#include "GameObject.h"
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"
#include "Asteroid.h"
#include "AsteroidFactory.h"
#include "SessionControl.h"

enum UpdateStatusEnum{
	ALL_SHIPS_BROKEN,
	TIME_OUT,
	UPDATING,
	PREPARING
};

class GameControl{
private:
	Logger* log = Logger::get_logger();
	vector<GameObject*>* objects;
	SessionControl* session_control;

	int update_status = PREPARING;
	int spaceships_count = 0;

public:
	GameControl() {
		this->objects = new vector<GameObject*>();
		this->session_control = new SessionControl(this->objects);
		//***************************************************************************************************************
		
		//***************************************************************************************************************
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

		this->update_status = this->session_control->update();
		return true;
	}

	void render() {
		log->info("GameControl rendering...");
		return;
	}

	int get_update_status() {
		return this->update_status;
	}
};

