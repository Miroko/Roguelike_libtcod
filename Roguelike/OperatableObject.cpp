#include "OperatableObject.h"
#include "Engine.h"

void OperatableObject::on(){
	isOn = true;
}

void OperatableObject::off(){
	isOn = false;
}

void OperatableObject::render(int x, int y){
	if (isOn){
		onGlyph.render(x, y);
	}
	else{
		offGlyph.render(x, y);
	}
}

void OperatableObject::messageDeath(){
	engine::gui.log.finishMessage(name + " is destroyed.");
}

void OperatableObject::onTakeDamageEffect(){
	
}

bool OperatableObject::passable(DynamicObject &dynamicObject){
	return DynamicObject::passable(dynamicObject);
}