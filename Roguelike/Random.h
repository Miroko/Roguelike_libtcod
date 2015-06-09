#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include "Direction.h"
class Random
{
public:
	static TCODRandom generator;

	static Point2D point(Rectangle &inBounds);
	static Point2D direction();
};
