#pragma once
#include <vector>
#include "GameObject.h"
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"
#include "Asteroid.h"
#include "AsteroidFactory.h"
#include "SessionControl.h"
#include "utils.h"

class GameControl{
private:
	Logger* log = new Logger("GameControl.log");
	vector<GameObject*>* objects;
	SessionControl* session_control;

	int update_status = PREPARING;
	int spaceships_count = 0;

	void game_session_complete() {
		log->info("Learning complete! All asteroids are skipped!");
		getchar();
	}

public:
	GameControl() {
		this->objects = new vector<GameObject*>();
		this->session_control = new SessionControl(this->objects);
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

		if (this->update_status == LEARNING_COMPLETE)
			game_session_complete();
		if (this->update_status == ALL_SHIPS_BROKEN)
			this->session_control->evaluate();

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

