#pragma once
#include "Point2D.h"
#include <vector>
#include <memory>

class Line
{
public:
	std::vector<std::shared_ptr<Point2D>> points;

	Line(Point2D &start, Point2D &end);
};

