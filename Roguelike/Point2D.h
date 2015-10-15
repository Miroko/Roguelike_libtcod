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

	//Euclidean distance
	int distance(Point2D &target);
	//Chebyshev distance
	int distanceChebyshev(Point2D &target);

	bool isUndefined();

	Point2D(int x, int y) : x(x), y(y){};
	Point2D(){};
};

struct Point2DHash {
	std::size_t operator()(const Point2D& point) const
	{
		return std::hash<int>()(point.x) ^ (std::hash<int>()(point.y) << 1);
	}
};

struct Point2DEqual {
	bool operator()(const Point2D& pointA, const Point2D& pointB) const
	{
		return pointA.x == pointB.x && pointA.y == pointB.y;
	}
};

static const Point2D POINT_UNDEFINED = Point2D();
