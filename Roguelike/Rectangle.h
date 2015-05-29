#pragma once
#include "Point2D.h"
class Rectangle
{
private:
	Point2D start;
	Point2D end;
public:
	float getWidth();
	float getHeight();
	Point2D getCenterPoint();
	bool contains(Point2D point);

	Rectangle(Point2D start, Point2D end) : start(start), end(end) {}
	Rectangle(){};
};

