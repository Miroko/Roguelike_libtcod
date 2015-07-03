#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include <memory>

class PlayerController
{
private:
	bool move(Point2D &direction);
	bool wait();
	bool attack(Point2D &direction);
	bool take();
	bool operate(Point2D &direction);
	bool talk(Point2D &direction);
	bool leaveArea();

public:
	//True if simulation update needed
	bool handleKey(TCOD_key_t key);

	PlayerController(){};
};

