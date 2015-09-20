#include "DynamicObject.h"
#include "EffectWaterSplash.h"
#include "EffectBloodSplatter.h"
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
	if (engine::areaHandler.getCurrentArea()->getTile(location)->type == Tile::WATER &&
		engine::playerHandler.getPlayerCreature()->ai->inFov(location)){
		engine::visualEffectHandler.playEffect(std::shared_ptr<ParticleEffect>(new EffectWaterSplash(location)));
	}
}
void DynamicObject::kill(){
	isDead = true;
	engine::areaHandler.getCurrentArea()->requireClean();
	onDeath();
}
bool DynamicObject::passable(DynamicObject &dynamicObject){
	return false;
}
void DynamicObject::onTakeDamage(DynamicObject &attacker, double amount){
	engine::gui.log.addToMessage(name + " takes " + std::to_string((int)amount) + " damage. ");
	if (amount > 0){
		healthHit(amount);
		onTakeDamageEffect();
	}
	if(!isDead) engine::gui.log.finishMessage();
}
void DynamicObject::onTakeDamageEffect(){
	engine::visualEffectHandler.playEffect(std::shared_ptr<ParticleEffect>(new EffectBloodSplatter(location)));
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
