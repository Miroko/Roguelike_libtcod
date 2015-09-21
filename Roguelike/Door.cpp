#include "Door.h"
#include "Engine.h"

void Door::operate(Creature &user){
	if (isOpen){
		if (engine::areaHandler.getCurrentArea()->getCreatures(location).empty()){
			transparent = false;
			isOpen = false;
			OperatableObject::operate(user);
		}
	}
	else{
		transparent = true;
		isOpen = true;
		OperatableObject::operate(user);
	}
}

bool Door::passable(DynamicObject &dynamicObject){
	if (isOpen) return true;
	else return false;
}


void Door::render(int x, int y){
	if (isOpen) onGlyph.render(x, y);
	else offGlyph.render(x, y);
}

std::shared_ptr<OperatableObject> Door::copy(){
	return std::shared_ptr<OperatableObject>(new Door(*this));
}
