#include "Rectangle.h"
#include "iostream"

float Rectangle::getWidth(){
	return end.x - start.x;
}

float Rectangle::getHeight(){
	return end.y - start.y;
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