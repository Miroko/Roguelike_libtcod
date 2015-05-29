#include "Camera.h"

int Camera::getWidth(){
	return TCODConsole::root->getWidth();
}

int Camera::getHeight(){	
	return TCODConsole::root->getHeight();
}

void Camera::move(int mx, int my){
	location.x += mx;
	location.y += my;
}

void Camera::centerOn(Point2D point){
	location.x = point.x - getWidth()/2;
	location.y = point.y - getHeight()/2;
}