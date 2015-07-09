#include "OperatableObject.h"
#include "Engine.h"

void OperatableObject::on(){
	isOn = true;
}

void OperatableObject::off(){
	isOn = false;
}

void OperatableObject::messageDeath(){
	engine::gui.log.finishMessage(name + " is destroyed.");
}

void OperatableObject::onTakeDamageEffect(){
	
}

bool OperatableObject::passable(DynamicObject &dynamicObject){
	return DynamicObject::passable(dynamicObject);
}


std::shared_ptr<OperatableObject> OperatableObject::copy(){
	return std::shared_ptr<OperatableObject>(new OperatableObject(*this));
}