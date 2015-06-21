#pragma once
#include <limits>
class Point2D
{

public:
	int x = INT_MAX;
	int y = INT_MAX;

	bool operator==(const Point2D &point);
	bool operator!=(const Point2D &point);
	Point2D operator+(const Point2D &point);
	Point2D operator-(const Point2D &point);
	Point2D& operator+=(const Point2D &point);
	Point2D& operator-=(const Point2D &point);

	int distance(Point2D &point);
	bool undefined();

	Point2D(int x, int y) : x(x), y(y){};
	Point2D(){};
};

