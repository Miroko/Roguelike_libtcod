#include "Rectangle.h"
#include "iostream"

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

bool Rectangle::contains(Point2D point){
	if (start.x <= point.x && point.x < end.x
		&& start.y <= point.y && point.y < end.y){
		return true;
	}
	else{
		return false;
	}
}