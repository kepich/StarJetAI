#pragma once
#include "GameObject.h"
class Factory{
public:
	virtual GameObject* get_object(double speed[2], int position[2], int type, int id) = 0;
};

