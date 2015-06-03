#include "Point2D.h"


bool Point2D::operator==(Point2D &point){
	return x == point.x && y == point.y;
}

bool Point2D::operator!=(Point2D &point){
	return x != point.x || y != point.y;
}


