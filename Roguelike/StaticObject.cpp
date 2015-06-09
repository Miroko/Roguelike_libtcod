#include "StaticObject.h"

bool StaticObject::passableBy(DynamicObject &dynamicObject){
	return !raised;
}