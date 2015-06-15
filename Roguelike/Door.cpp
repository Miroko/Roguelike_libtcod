#include "Door.h"

bool Door::passable(){
	return isOn;
}

void Door::on(){
	OperatableObject::on();
	transparent = true;
}

void Door::off(){
	OperatableObject::off();
	transparent = false;
}