#include "DynamicObject.h"
#include "Engine.h"

bool DynamicObject::move(Point2D &location){
	if (engine::areaHandler.getCurrentArea()->passable(location, *this)){
		this->location = location;
		onMove();
		return true;
	}
	else return false;
}
void DynamicObject::onMove(){
	engine::visualEffectPlayer.playEffect(
		location,
		engine::areaHandler.getCurrentArea()->getTile(location)->visualEffectOnCollision);
}
void DynamicObject::kill(){
	isDead = true;
	engine::areaHandler.getCurrentArea()->requireClean();
	onDeath();
}
bool DynamicObject::passable(DynamicObject &dynamicObject){
	return false;
}
void DynamicObject::takeDamage(DynamicObject &attacker, double amount){
	engine::gui.log.addToMessage(name + " takes " + std::to_string((int)amount) + " damage. ");
	if (amount > 0){
		healthHit(amount);
		engine::visualEffectPlayer.playEffect(location, visualEffectOnTakeDamage);
	}
	if(!isDead) engine::gui.log.finishMessage();
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
	if (healthCurrent <= 0)	kill();
	else if (healthCurrent > getHealthMax()) healthCurrent = getHealthMax();
}
