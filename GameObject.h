#pragma once
using namespace std;

enum GAME_OBJECT_TYPE
{
	EMPTY_OBJECT,
	SPACESHIP,
	ASTEROID
};

class GameObject{
protected:
	float	speed[2]		= { 0, 0 };
	float	position[2]		= { 0, 0 };
	int		size[2]			= { 0, 0 };
	int		type			= EMPTY_OBJECT;
	int		id				= -1;
	bool	is_deleted_flag	= false;

public:
	GameObject(float speed[2], float position[2], int size[2], int type, int id) {
		this->speed[0] = speed[0];			// Speed vector
		this->speed[1] = speed[1];

		this->position[0] = position[0];	// X; Y coords
		this->position[1] = position[1];

		this->size[0] = size[0];			// WIDTH; HEIGHT
		this->size[1] = size[1];

		this->type = type;
		this->id = id;
	}

	bool is_deleted() {
		return this->is_deleted_flag;
	}

	vector<float>* get_obj_rect() {
		vector<float>* res = new vector<float>();
		res->push_back(this->position[0]);
		res->push_back(float(this->size[0]));
		res->push_back(this->position[1]);
		res->push_back(float(this->size[1]));
		return res;
	}

	float* get_speed() {
		return this->speed;
	}

	float* get_position() {
		return this->position;
	}

	int get_type() {
		return this->type;
	}

	virtual bool update() = 0;

	virtual void render() = 0;
};

