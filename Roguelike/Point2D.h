#pragma once
#include <limits>
class Point2D
{

public:
	float x = FLT_MAX;
	float y = FLT_MAX;

	bool operator==(const Point2D &point);
	bool operator!=(const Point2D &point);
	Point2D operator-(const Point2D &point);
	Point2D operator+(const Point2D &point);

	bool undefined();

	Point2D(float x, float y) : x(x), y(y){};
	Point2D(){};
};

