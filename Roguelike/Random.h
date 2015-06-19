#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include "Direction.h"
#include <memory>
class Random
{
private:
	static std::shared_ptr<TCODRandom> randomState;
	static std::shared_ptr<TCODRandom> staticState;
public:
	static TCODRandom generator;

	static Point2D point(Rectangle &inBounds);
	static Point2D direction();
	static void useStatic();
	static void useRandom();
	static void reset();
};
