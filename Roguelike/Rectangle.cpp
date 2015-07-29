#include "Rectangle.h"
#include "Direction.h"

Rectangle::Rectangle(Point2D start, Point2D end) {
	this->start = start;
	this->end = end;
}

Rectangle::Rectangle(int width, int height) {
	this->start = Point2D(0, 0);
	this->end = Point2D(width, height);
}

Rectangle::Rectangle(Point2D center, int size) :
Rectangle(center, center){ 
	expand(size);
}

int Rectangle::getWidth(){
	return (int)(end.x + 1 - start.x);
}

int Rectangle::getHeight(){
	return (int)(end.y + 1 - start.y);
}

int Rectangle::getSize(){
	return (int)(getWidth() * getHeight());
}

Point2D Rectangle::getCenterPoint(){
	return Point2D(start.x + getWidth()/2, start.y + getHeight()/2);
}

bool Rectangle::inside(Point2D &point){
	if (start.x < point.x && point.x < end.x
		&& start.y < point.y && point.y < end.y){
		return true;
	}
	else{
		return false;
	}
}

bool Rectangle::contains(Point2D &point){
	if (start.x <= point.x && point.x <= end.x
		&& start.y <= point.y && point.y <= end.y){
		return true;
	}
	else{
		return false;
	}
}

std::vector<Point2D> Rectangle::getEdgePoints(){
	std::vector<Point2D> points;
		
	for (int x = start.x; x <= end.x; x++){
		points.push_back(Point2D(x, start.y));
		points.push_back(Point2D(x, end.y));
	}
	for (int y = start.y; y <= end.y; y++){
		points.push_back(Point2D(start.x, y));
		points.push_back(Point2D(end.x, y));
	}

	return points;
}

Rectangle Rectangle::expand(int amount){
	start.x -= amount;
	start.y -= amount;
	end.x += amount;
	end.y += amount;
	return *this;
}

Rectangle Rectangle::shrink(int amount){
	start.x += amount;
	start.y += amount;
	end.x -= amount;
	end.y -= amount;
	return *this;
}