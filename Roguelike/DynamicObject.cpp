#include "DynamicObject.h"
#include "Engine.h"
#include "ObjectLibrary.h"

bool DynamicObject::passable(DynamicObject &dynamicObject){
	return false;
}

void DynamicObject::onTakeDamage(DynamicObject &attacker, int amount){
	Engine::GUI.log.addToMessage(name + " takes " + std::to_string(amount) + " damage. ");

	if (amount > 0){
		health -= amount;
		onTakeDamageEffect();
	}

	if (health <= 0) onDeath();
	else Engine::GUI.log.finishMessage("");
}

void DynamicObject::onTakeDamageEffect(){
	Engine::visualEffectHandler.playEffect(location, Random::direction(), VisualEffect::BLOOD_SPLATTER);
}

void DynamicObject::onDeath(){
	messageDeath();
	ObjectLibrary::generateLootDrop(Engine::area, *this);
	Engine::area.killDynamicObject(*this);
}

void DynamicObject::messageDeath(){
	Engine::GUI.log.finishMessage(name + " dies.");
}

void DynamicObject::setHealth(int health){
	this->healthMax = health;
	this->health = health;
}