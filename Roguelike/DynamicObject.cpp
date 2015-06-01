#include "DynamicObject.h"
#include "StaticObject.h"
#include "iostream"

bool DynamicObject::isBlockedBy(DynamicObject &object){
	if (this->size == SMALL) return false;
	else{
		return true;
	}
}