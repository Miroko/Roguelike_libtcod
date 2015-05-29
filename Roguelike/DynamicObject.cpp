#include "DynamicObject.h"
#include "StaticObject.h"
#include "iostream"

void DynamicObject::update(float elapsed){
	/*
	sleep -= elapsed;
	if (sleep <= 0){
	move(1, 0);
	sleep = speed;
	}
	*/
}

bool Human::isBlockedBy(DynamicObject &object){
	if (object.size == SMALL) return false;
	else return true;
}
