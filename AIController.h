#pragma once
#include "Controller.h"
#include "CONF.h"
#include "GameObject.h"
#include "Asteroid.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <dvec.h>
#include <ctime>

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
	float input_layer_0		[INPUT_L_SIZE][INPUT_SIZE];
	float hidden_layer_1	[HIDDEN_1_SIZE][INPUT_L_SIZE];
	float hidden_layer_2	[HIDDEN_2_SIZE][HIDDEN_1_SIZE];
	float output_layer		[OUTPUT_SIZE][HIDDEN_2_SIZE];

	vector<GameObject*>* game_objects;
	GameObject* host_object;

	float activate(float res) {
		float ex = exp(-res);
		return ((1 / (1 + ex)) > TRIGGER_LIMIT) ? 1.0f : 0.0f;
	}

public:
	AIController(vector<GameObject*>* game_objects):Controller(AI) {
		this->game_objects = game_objects;
		int i, j;
		srand(int(time(NULL)));

		for (i = 0; i < INPUT_L_SIZE; i++)
			for (j = 0; j < INPUT_SIZE; j++)
				this->input_layer_0[i][j] = 0.01f * (rand() % 101);

		for (i = 0; i < HIDDEN_1_SIZE; i++)
			for (j = 0; j < INPUT_L_SIZE; j++)
				this->hidden_layer_1[i][j] = 0.01f * (rand() % 101);

		for (i = 0; i < HIDDEN_2_SIZE; i++)
			for (j = 0; j < HIDDEN_1_SIZE; j++)
				this->hidden_layer_2[i][j] = 0.01f * (rand() % 101);

		for (i = 0; i < OUTPUT_SIZE; i++)
			for (j = 0; j < HIDDEN_2_SIZE; j++)
				this->output_layer[i][j] = 0.01f * (rand() % 101);
	}

	void set_host_object(GameObject* host) {
		this->host_object = host;
	}

	pair<float, float> get_move() {
		Asteroid* asteroid = nullptr;
		for (auto i = this->game_objects->begin(); i < this->game_objects->end(); i++)
			if ((*i)->get_type() == ASTEROID) {
				asteroid = (Asteroid*) *i;
				break;
			}


		GameObject* host = this->host_object;
		float* buffer_accum1 = new float[INPUT_SIZE];

		buffer_accum1[0] = (float)(host->get_position()[0] / GAMEFIELD_WIDTH);
		buffer_accum1[1] = (float)(host->get_position()[1] / GAMEFIELD_HEIGHT);
		buffer_accum1[2] = (float)((host->get_speed()[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED);
		buffer_accum1[3] = (float)((host->get_speed()[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED);
		buffer_accum1[4] = (float)(asteroid->get_position()[0] / GAMEFIELD_WIDTH);
		buffer_accum1[5] = (float)(asteroid->get_position()[1] / GAMEFIELD_HEIGHT);
		buffer_accum1[6] = (float)((asteroid->get_speed()[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED);
		buffer_accum1[7] = (float)((asteroid->get_speed()[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED);
		// INPUT INIT
		__m256 input_data = _mm256_load_ps(buffer_accum1);

		float* buffer_accum2 = new float[INPUT_L_SIZE];
		
		// Умножение на INPUT_LAYER **************************************
		for (int i = 0; i < INPUT_L_SIZE; i++)					// SIMD умножение матрицы на вектор
			buffer_accum2[i] = _mm256_reduce_add_ps(_mm256_mul_ps(input_data, _mm256_load_ps(this->input_layer_0[i])));
		delete[] buffer_accum1;

		// Умножение на HIDDEN_LAYER_1 ***********************************
		buffer_accum1 = new float[HIDDEN_1_SIZE];
		__m256 lo = _mm256_load_ps(buffer_accum2), hi = _mm256_load_ps(&buffer_accum2[8]);
		for (int i = 0; i < HIDDEN_1_SIZE; i++)
			buffer_accum1[i] = _mm256_reduce_add_ps(_mm256_mul_ps(lo, _mm256_load_ps(this->hidden_layer_1[i])), 
				_mm256_mul_ps(hi, _mm256_load_ps(&this->hidden_layer_1[i][8])));
		delete[] buffer_accum2;

		// Умножение на HIDDEN_LAYER_2 ***********************************
		lo = _mm256_load_ps(buffer_accum1);
		hi = _mm256_load_ps(&buffer_accum1[8]);
		buffer_accum2 = new float[HIDDEN_2_SIZE];
		for(int i = 0; i < HIDDEN_2_SIZE; i++)
			buffer_accum2[i] = _mm256_reduce_add_ps(_mm256_mul_ps(lo, _mm256_load_ps(this->hidden_layer_2[i])),
				_mm256_mul_ps(hi, _mm256_load_ps(&this->hidden_layer_2[i][8])));
		delete[] buffer_accum1;

		// Умножение на OUTPUT_LAYER *************************************
		buffer_accum1 = new float[OUTPUT_SIZE];
		lo = _mm256_load_ps(buffer_accum2);
		hi = _mm256_load_ps(&buffer_accum2[8]);
		for (int i = 0; i < OUTPUT_SIZE; i++)
			buffer_accum1[i] = _mm256_reduce_add_ps(_mm256_mul_ps(lo, _mm256_load_ps(this->output_layer[i])),
				_mm256_mul_ps(hi, _mm256_load_ps(&this->output_layer[i][8])));
		delete[] buffer_accum2;

		// В buffer_accum2 - резуьтат
		pair<int, int> result(0, 0);
		for (int i = 0; i < OUTPUT_SIZE; i++)
			buffer_accum1[i] = this->activate(buffer_accum1[i]);
		
		if (buffer_accum1[0])
			result.second += 1;
		if (buffer_accum1[1])
			result.second -= 1;
		if (buffer_accum1[0])
			result.first += 1;
		if (buffer_accum1[0])
			result.first -= 1;

		return result;
	}
};

