#include "Door.h"
#include "Engine.h"

void Door::operate(Creature &user){
	if (isOpen){
		//close
		if (!&engine::areaHandler.getCurrentArea()->getCreature(location)){
			isOpen = false;
			glyph = offGlyph;
			OperatableObject::operate(user);
		}
	}
	else{
		//open
		isOpen = true;
		glyph = onGlyph;
		OperatableObject::operate(user);
	}
}

bool Door::isPassable(DynamicObject &dynamicObject){
	if (isOpen) return true;
	else return false;
}

std::shared_ptr<OperatableObject> Door::copy(){
	return std::shared_ptr<OperatableObject>(new Door(*this));
}
