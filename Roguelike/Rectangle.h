#pragma once
#include "Point2D.h"
class Rectangle
{
public:
	Point2D start;
	Point2D end;

	int getWidth();
	int getHeight();
	int getSize();
	Point2D getCenterPoint();
	bool contains(Point2D point);

	Rectangle(Point2D start, Point2D end) : start(start), end(end) {}
	Rectangle(){};
};

