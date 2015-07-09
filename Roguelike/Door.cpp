#include "Door.h"
#include "Engine.h"

void Door::on(){
	transparent = true;
	OperatableObject::on();
}

void Door::off(){
	if (engine::areaHandler.getCurrentArea()->getCreatures(location).empty()){
		transparent = false;
		OperatableObject::off();
	}
}

bool Door::passable(DynamicObject &dynamicObject){
	if (isOn) return true;
	else return false;
}


void Door::render(int x, int y){
	if (isOn){
		onGlyph.render(x, y);
	}
	else{
		offGlyph.render(x, y);
	}
}

std::shared_ptr<OperatableObject> Door::copy(){
	return std::shared_ptr<OperatableObject>(new Door(*this));
}
