#pragma once
#include "Rectangle.h"
#include "libtcod.hpp"

class Callback : public ITCODPathCallback{
public:
	float getWalkCost(int fromX, int fromY, int toX, int toY, void *data) const;
};

class PathFinder
{
private:
	
public:
	TCODPath *pathComputerAStar;
	
	PathFinder(Rectangle bounds);
	PathFinder(){};
};

