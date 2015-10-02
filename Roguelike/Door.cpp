#include "Door.h"
#include "Engine.h"

void Door::operate(Creature &user){
	if (isOpen){
		//close
		if (!&engine::areaHandler.getCurrentArea()->getCreature(location)){
			transparent = false;
			isOpen = false;
			OperatableObject::operate(user);
		}
	}
	else{
		//open
		transparent = true;
		isOpen = true;
		OperatableObject::operate(user);
	}
}

bool Door::isPassable(DynamicObject &dynamicObject){
	if (isOpen) return true;
	else return false;
}


void Door::render(int x, int y,double intensity){
	if (isOpen) onGlyph.render(x, y, intensity);
	else offGlyph.render(x, y, intensity);
}

std::shared_ptr<OperatableObject> Door::copy(){
	return std::shared_ptr<OperatableObject>(new Door(*this));
}
