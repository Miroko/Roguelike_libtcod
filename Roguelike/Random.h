#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include <memory>

class Random
{
private:
	std::shared_ptr<TCODRandom> randomState;
	std::shared_ptr<TCODRandom> staticState;

public:
	std::shared_ptr<TCODRandom> generator;

	Point2D point(Rectangle &inBounds);
	Point2D direction();
	bool chance(float min);

	void init();
	void useStatic();
	void useRandom();
};
