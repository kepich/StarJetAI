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
	float input_layer_0		[INPUT_L_SIZE][INPUT_SIZE];
	float hidden_layer_1	[HIDDEN_1_SIZE][INPUT_L_SIZE];
	float hidden_layer_2	[HIDDEN_1_SIZE][HIDDEN_2_SIZE];
	float output_layer		[HIDDEN_2_SIZE][OUTPUT_SIZE];

	vector<GameObject*>* game_objects;
	GameObject* host_object;

	float activate(float res) {
		return (1 / (1 + exp(-res)) > TRIGGER_LIMIT) ? 1 : 0;
	}

public:
	AIController(vector<GameObject*>* game_objects):Controller(AI) {
		this->game_objects = game_objects;
	}

	void set_host_object(GameObject* host) {
		this->host_object = host;
	}

	pair<float, float> get_move() {
		Asteroid* asteroid = nullptr;
		for (auto i = --(this->game_objects->end()); i >= this->game_objects->begin(); i--)
			if ((*i)->get_type() == ASTEROID) {
				asteroid = (Asteroid*) *i;
				break;
			}


		Spaceship* host = (Spaceship*)this->host_object;
		// INPUT INIT
		F32vec8* input_data = new F32vec8(
			host->position[0] / GAMEFIELD_WIDTH,
			host->position[1] / GAMEFIELD_HEIGHT,
			(host->speed[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			(host->speed[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			asteroid->position[0] / GAMEFIELD_WIDTH,
			asteroid->position[1] / GAMEFIELD_HEIGHT,
			(asteroid->speed[0] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED,
			(asteroid->speed[1] + SPACESHIP_LINEAR_MAX_SPEED) / SPACESHIP_LINEAR_MAX_SPEED / SPACESHIP_LINEAR_MAX_SPEED
		);

		float* buffer_accum1 = new float[INPUT_SIZE];
		float* buffer_accum2 = new float[INPUT_L_SIZE];
		
		// Умножение на INPUT_LAYER **************************************
		for (int i = 0; i < INPUT_L_SIZE; i++) {					// SIMD умножение матрицы на вектор
			_mm256_store_ps(buffer_accum1, _mm256_mul_ps(*input_data, _mm256_load_ps(this->input_layer_0[i])));

			for (int j = 1; j < INPUT_SIZE; j++)
				buffer_accum1[0] += buffer_accum1[j];
			buffer_accum2[i] = buffer_accum1[0];
		}
		delete input_data;
		delete[] buffer_accum1;

		// Умножение на HIDDEN_LAYER_1 ***********************************
		buffer_accum1 = new float[HIDDEN_1_SIZE];
		__m512* inp_result = &_mm512_load_ps(buffer_accum2);
		for (int i = 0; i < HIDDEN_1_SIZE; i++)
			buffer_accum1[i] = _mm512_reduce_add_ps(_mm512_mul_ps(*inp_result, _mm512_load_ps(this->hidden_layer_1[i])));
		delete[] buffer_accum2;

		// Умножение на HIDDEN_LAYER_2 ***********************************
		buffer_accum2 = new float[HIDDEN_2_SIZE];
		inp_result = &_mm512_load_ps(buffer_accum1);
		for(int i = 0; i < HIDDEN_2_SIZE; i++)
			buffer_accum2[i] = _mm512_reduce_add_ps(_mm512_mul_ps(*inp_result, _mm512_load_ps(this->hidden_layer_2[i])));
		delete[] buffer_accum1;

		// Умножение на OUTPUT_LAYER *************************************
		buffer_accum1 = new float[OUTPUT_SIZE];
		inp_result = &_mm512_load_ps(buffer_accum2);
		for (int i = 0; i < HIDDEN_1_SIZE; i++)
			buffer_accum1[i] = _mm512_reduce_add_ps(_mm512_mul_ps(*inp_result, _mm512_load_ps(this->hidden_layer_1[i])));
		delete[] buffer_accum2;

		// В buffer_accum2 - резуьтат
		pair<int, int> result(0, 0);
		for (int i = 0; i < OUTPUT_SIZE; i++)
			buffer_accum2[i] = this->activate(buffer_accum2[i]);
		
		if (buffer_accum2[0])
			result.second += 1;
		if (buffer_accum2[1])
			result.second -= 1;
		if (buffer_accum2[0])
			result.first += 1;
		if (buffer_accum2[0])
			result.first -= 1;


		return result;
	}
};

