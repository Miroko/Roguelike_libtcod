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

Point2D& Point2D::operator+=(const Point2D &point){
	this->x += point.x;
	this->y += point.y;
	return *this;
}

Point2D& Point2D::operator-=(const Point2D &point){
	this->x -= point.x;
	this->y -= point.y;
	return *this;
}

int Point2D::distance(Point2D &point){
	return (int)sqrt((point.x - x) * (point.x - x) + (point.y - y) * (point.y - y));
}

bool Point2D::undefined(){
	return x == INT_MAX && y == INT_MAX;
}