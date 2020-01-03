#pragma once
#include "Controller.h"
#include "CONF.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
using namespace std;

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
	float input_layer[8];
	float hidden_layer_1[16][8];
	float hidden_layer_2[16][16];
	float output_layer[4][16];

public:

	AIController(vector<GameObject*>* game_objects) {

	}

	pair<double, double> get_move() {
		return pair<int, int>(1, 1);
	}
};

