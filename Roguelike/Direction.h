#pragma once
#include "Point2D.h"
class Direction
{
public:
	Direction(){};
};

const Point2D DOWN_LEFT = Point2D(-1, 1);
const Point2D LEFT = Point2D(-1, 0);
const Point2D UP_LEFT = Point2D(-1, -1);
const Point2D UP = Point2D(0, -1);
const Point2D UP_RIGHT = Point2D(1, -1);
const Point2D RIGHT = Point2D(1, 0);
const Point2D DOWN_RIGHT = Point2D(1, 1);
const Point2D DOWN = Point2D(0, 1);

const Point2D DIRECTIONS[] = { DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN };

const Point2D CENTER = Point2D(0, 0);
