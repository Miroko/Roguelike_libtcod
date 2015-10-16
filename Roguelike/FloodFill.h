#pragma once
#include "Area.h"
#include "Rectangle.h"
#include <deque>
#include <functional>

class FloodFill
{
private:
	enum LocationState : char
	{
		UNFILLED,
		FILL_NEXT,
		FILLED
	};
	std::deque<Point2D> locations;
	std::vector<std::vector<LocationState>> locationStates;

public:
	//flood bounds from center location
	void flood(
		Rectangle &bounds,
		double percentage,
		std::function<bool(Point2D &location)> isPassable, 
		std::function<void(Point2D &location, int distance)> onLocationFill);

	FloodFill(){};
};

