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

int Point2D::distance(Point2D &target){
	return 
		(int)sqrt(
		(target.x - x) * (target.x - x) +
		(target.y - y) * (target.y - y));
}

int Point2D::distanceChebyshev(Point2D &target){
	return
		std::abs(x - target.x) +
		std::abs(y - target.y);
}

bool Point2D::isUndefined(){
	return x == INT_MAX && y == INT_MAX;
}