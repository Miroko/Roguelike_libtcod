#include "DynamicObject.h"
#include "StaticObject.h"
#include "Engine.h"
#include "iostream"

bool DynamicObject::isBlockedBy(DynamicObject &object){
	if (this->size == SMALL) return false;
	else{
		return true;
	}
}

void DynamicObject::onTakeDamage(int amount){
	Engine::log.addToMessage(name + " takes " + std::to_string(amount) + " damage. ");
	health -= amount;
	if (health <= 0){
		onDeath();
	}
	else{
		Engine::log.finishMessage("");
	}
}

void DynamicObject::onDeath(){
	Engine::log.finishMessage(name + " dies.");
	Engine::area.killDynamicObject(*this);
}