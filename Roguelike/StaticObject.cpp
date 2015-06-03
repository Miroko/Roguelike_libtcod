#include "StaticObject.h"

bool StaticObject::isPassableBy(DynamicObject &dynamicObject){
	return false;
}

bool Land::isPassableBy(DynamicObject &dynamicObject){
	return true;
}

bool StoneFloor::isPassableBy(DynamicObject &dynamicObject){
	return true;
}