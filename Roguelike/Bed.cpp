#include "Bed.h"

bool Bed::isInUse(){
	return user != nullptr;
}

void Bed::operate(Creature &user){
	if (!isInUse()){
		this->user = &user;
	}
	else if (this->user == &user){
		this->user = nullptr;
	}
}

bool Bed::isPassable(DynamicObject &dynamicObject){
	return true;
}

std::shared_ptr<OperatableObject> Bed::copy(){
	return std::shared_ptr<OperatableObject>(new Bed(*this));
}