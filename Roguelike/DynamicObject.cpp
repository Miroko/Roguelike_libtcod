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
	health -= amount;
	if (health <= 0){
		onDeath();
	}
}

void DynamicObject::onDeath(){
	Engine::area.removeDynamicObject(*this);
}