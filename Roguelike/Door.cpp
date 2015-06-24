#include "Door.h"
#include "Engine.h"

bool Door::passable(){
	return isOn;
}

void Door::on(){
	OperatableObject::on();
	transparent = true;
}

void Door::off(){
	if (Engine::area.getCreatures(location).empty()){
		OperatableObject::off();
		transparent = false;
	}
}