#include "Door.h"
#include "Engine.h"

void Door::on(){
	transparent = true;
	OperatableObject::on();
}

void Door::off(){
	if (Engine::area.getCreatures(location).empty()){
		transparent = false;
		OperatableObject::off();
	}
}

bool Door::passable(DynamicObject &dynamicObject){
	if (isOn) return true;
	else return false;
}