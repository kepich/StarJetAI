#pragma once
#include "Controller.h"
#include "CONF.h"
#include "GameObject.h"
#include "Asteroid.h"
#include <iostream>
#include <vector>
#include <dvec.h>

using namespace std;

#define INPUT_SIZE 8
#define INPUT_L_SIZE 16
#define HIDDEN_1_SIZE 16
#define HIDDEN_2_SIZE 16
#define OUTPUT_SIZE 4

class AIController : public Controller{
private:
	/* INPUT: 
	spaceship_pos_X
	spaceship_pos_Y
	spaceship_speed_X
	spaceship_speed_Y
	asteroid_pos_X
	asteroid_pos_Y
	asteroid_speed_X
	asteroid_speed_Y
	*/
	float input_layer_0		[INPUT_SIZE][INPUT_L_SIZE];
	float hidden_layer_1	[INPUT_L_SIZE][HIDDEN_1_SIZE];
	float hidden_layer_2	[HIDDEN_1_SIZE][HIDDEN_2_SIZE];
	float output_layer		[HIDDEN_2_SIZE][OUTPUT_SIZE];

	vector<GameObject*>* game_objects;
	GameObject* host_object;

public:
	AIController(vector<GameObject*>* game_objects):Controller(AI) {
		this->game_objects = game_objects;
	}

	void set_host_object(GameObject* host) {
		this->host_object = host;
	}

	pair<float, float> get_move() {
		int* input_data = new int[INPUT_SIZE];
		Asteroid* asteroid = nullptr;
		for (auto i = --(this->game_objects->end()); i >= this->game_objects->begin(); i--)
			if ((*i)->get_type() == ASTEROID) {
				asteroid = (Asteroid*) *i;
				break;
			}

		Spaceship* host = (Spaceship*)this->host_object;
		// INPUT INIT
		F32vec8 input_data(
			host->position[0] / GAMEFIELD_WIDTH,
			host->position[1] / GAMEFIELD_HEIGHT,
			(host->speed[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			(host->speed[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			asteroid->position[0] / GAMEFIELD_WIDTH,
			asteroid->position[1] / GAMEFIELD_HEIGHT,
			(asteroid->speed[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			(asteroid->speed[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED
		);
		
		

		return pair<int, int>(1, 1);
	}
};

