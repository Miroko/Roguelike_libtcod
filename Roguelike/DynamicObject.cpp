#include "DynamicObject.h"
#include "Engine.h"

bool DynamicObject::move(Point2D &location){
	if(engine::areaHandler.getCurrentArea()->moveDynamicObject(*this, location)){
		onMove();
		return true;
	}
	else return false;
}

void DynamicObject::onMove(){
	engine::visualEffectPlayer.playEffect(location,	engine::areaHandler.getCurrentArea()->getTile(location)->visualEffectOnCollision);
}

void DynamicObject::destroy(){
	onDeath();
	engine::areaHandler.getCurrentArea()->destroyDynamicObject(*this);
}

bool DynamicObject::isPassable(DynamicObject &dynamicObject){
	return false;
}

void DynamicObject::takeDamage(DynamicObject &attacker, double amount){
	engine::gui.log.finishMessage(name + " takes " + std::to_string((int)amount) + " damage. ");
	if (amount > 0){
		engine::visualEffectPlayer.playEffect(location, visualEffectOnTakeDamage);
		healthHit(amount);
	}
}

void DynamicObject::onDeath(){
	messageDeath();
}

void DynamicObject::messageDeath(){
	engine::gui.log.finishMessage(name + " dies.");
}

int DynamicObject::getHealthCurrent(){
	return healthCurrent;
}

int DynamicObject::getHealthMax(){
	return healthMax;
}

void DynamicObject::healthHit(int amount){
	healthCurrent -= amount;
	if (healthCurrent <= 0)	destroy();
	else if (healthCurrent > getHealthMax()) healthCurrent = getHealthMax();
}
