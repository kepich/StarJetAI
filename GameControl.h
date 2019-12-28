#pragma once
#include "Logger.h"
#include "Spaceship.h"
#include "SpaceshipFactory.h"

class GameControl{
private:
	Logger* log = Logger::get_logger();
public:
	GameControl() {
		return;
	}

	bool update() {
		log->info("GameControl updating...");
		return true;
	}

	void render() {
		log->info("GameControl rendering...");
		return;
	}
};

