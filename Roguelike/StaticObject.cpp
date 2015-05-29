#include "StaticObject.h"


bool Land::isPassableBy(DynamicObject &dynamicObject){
	return true;
}

bool Wall::isPassableBy(DynamicObject &dynamicObject){
	return false;
}


