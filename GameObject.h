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
	int		type			= EMPTY_OBJECT;
	int		id				= -1;
	bool	is_deleted_flag	= false;

public:
	GameObject(double speed[2], int position[2], int type, int id) {
		this->speed[0] = speed[0];
		this->speed[1] = speed[1];

		this->position[0] = position[0];
		this->position[1] = position[1];

		this->type = type;
		this->id = id;
	}

	bool is_deleted() {
		return this->is_deleted_flag;
	}

	virtual bool update() = 0;

	virtual void render() = 0;
};

