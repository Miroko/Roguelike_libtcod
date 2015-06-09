#include "DynamicObject.h"
#include "Engine.h"

bool DynamicObject::isBlockedBy(DynamicObject &object){
	if (this->size == SMALL) return false;
	else{
		return true;
	}
}

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

std::vector<std::shared_ptr<Item>> DynamicObject::generateLoot(){
	std::vector<std::shared_ptr<Item>> items;
	for (auto &weapon : loot.weapons){
		items.push_back(Item::newItem<Weapon>(weapon));
	}
	return items;
}

void DynamicObject::onDeath(){
	for (auto &item : generateLoot()){
		Engine::area.placeItem(item, location);
	}

	Engine::GUI.log.finishMessage(name + " dies.");
	Engine::area.killDynamicObject(*this);
}