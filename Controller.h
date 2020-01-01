#pragma once

enum MoveDirection{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Controller{
public:
	virtual int get_move() = 0;
};

