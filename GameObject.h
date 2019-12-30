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
	double	speed[2]		= { 0, 0 };
	int		position[2]		= { 0, 0 };
	int		size[2]			= { 0, 0 };
	int		type			= EMPTY_OBJECT;
	int		id				= -1;
	bool	is_deleted_flag	= false;

public:
	GameObject(double speed[2], int position[2], int size[2], int type, int id) {
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

	vector<int>* get_obj_rect() {
		vector<int> res;
		res.push_back(this->position[0]), res.push_back(this->size[0]), res.push_back(this->position[1]), res.push_back(this->size[1]);
		return &res;
	}

	int get_type() {
		return this->type;
	}

	virtual bool update() = 0;

	virtual void render() = 0;
};

