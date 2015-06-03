#pragma once
class Point2D
{

public:
	float x = 0;
	float y = 0;

	bool operator==(Point2D &point);
	bool operator!=(Point2D &point);

	Point2D(float x, float y) : x(x), y(y){};
	Point2D(){};
};

