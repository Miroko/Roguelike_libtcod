#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Rectangle.h"

class Camera
{
private:

public:
	Point2D location;

	int getWidth();
	int getHeight();

	void move(int mx, int my);

	void centerOn(Point2D point);

	Camera(Point2D location) : location(location){};
	Camera(){};
};

