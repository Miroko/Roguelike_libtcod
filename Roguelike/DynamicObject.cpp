#include "DynamicObject.h"
#include "Engine.h"

void DynamicObject::onTakeDamage(int amount){
	Engine::GUI.log.addToMessage(name + " takes " + std::to_string(amount) + " damage. ");
	health -= amount;
	if (health <= 0){
		onDeath();
	}
	else{
		Engine::GUI.log.finishMessage("");
	}
}

void DynamicObject::onDeath(){
	for (auto &item : loot.generateLoot()){
		Engine::area.placeItem(item, location);
	}

	messageDeath();
	Engine::area.killDynamicObject(*this);
}

void DynamicObject::messageDeath(){
	Engine::GUI.log.finishMessage(name + " dies.");
}