#include "Bed.h"

bool Bed::passable(DynamicObject &dynamicObject){
	return true;
}

std::shared_ptr<OperatableObject> Bed::copy(){
	return std::shared_ptr<OperatableObject>(new Bed(*this));
}