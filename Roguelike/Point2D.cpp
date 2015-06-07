#include "Point2D.h"

bool Point2D::operator==(const Point2D &point){
	return x == point.x && y == point.y;
}

bool Point2D::operator!=(const Point2D &point){
	return x != point.x || y != point.y;
}

Point2D Point2D::operator-(const Point2D &point){
	return Point2D(x - point.x, y - point.y);
}

Point2D Point2D::operator+(const Point2D &point){
	return Point2D(x + point.x, y + point.y);
}

bool Point2D::undefined(){
	return x == FLT_MAX && y == FLT_MAX;
}