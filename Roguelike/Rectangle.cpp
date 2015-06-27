#include "Rectangle.h"
#include "Direction.h"

Rectangle::Rectangle(Point2D start, Point2D end) {
	this->start = start;
	this->end = end;
}

int Rectangle::getWidth(){
	return (int)(end.x - start.x);
}

int Rectangle::getHeight(){
	return (int)(end.y - start.y);
}

int Rectangle::getSize(){
	return (int)(getWidth() * getHeight());
}

Point2D Rectangle::getCenterPoint(){
	return Point2D(start.x + getWidth()/2, start.y + getHeight()/2);
}

bool Rectangle::inside(Point2D &point){
	if (start.x <= point.x && point.x < end.x
		&& start.y <= point.y && point.y < end.y){
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

std::vector<Point2D> Rectangle::getPoints(){
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

void Rectangle::expand(int amount){
	start.x -= amount;
	start.y -= amount;
	end.x += amount;
	end.y += amount;
}

void Rectangle::shrink(int amount){
	start.x += amount;
	start.y += amount;
	end.x -= amount;
	end.y -= amount;
}