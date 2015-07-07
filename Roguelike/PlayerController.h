#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include <memory>

class PlayerController
{
private:
	bool move(Point2D &direction);
	bool wait();
	bool attack();
	bool take();
	bool operate();
	bool talk();
	bool enterArea();
	bool leaveArea();

public:
	//True if simulation update needed
	bool handleKey(TCOD_key_t key);

	PlayerController(){};
};

