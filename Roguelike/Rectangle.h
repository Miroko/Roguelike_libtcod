#pragma once
#include "Point2D.h"
#include <vector>

class Rectangle
{
public:
	Point2D start;
	Point2D end;

	int getWidth();
	int getHeight();
	int getSize();
	Point2D getCenterPoint();
	bool inside(Point2D &point);
	bool contains(Point2D &point);
	Rectangle expand(int amount);
	Rectangle shrink(int amount);
	std::vector<Point2D> getEdgePoints();

	Rectangle(Point2D start, Point2D end);
	Rectangle(Point2D center, int size);
	Rectangle(int width, int height);
	Rectangle(){};
};

