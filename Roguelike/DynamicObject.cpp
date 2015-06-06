#include "DynamicObject.h"
#include "StaticObject.h"
#include "Engine.h"
#include <list>

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

std::vector<std::shared_ptr<Item>> DynamicObject::generateLoot(){
	std::vector<std::shared_ptr<Item>> items;
	for (const Item &item : loot.items){
		items.push_back(std::shared_ptr<Item>(new Item(item)));
	}
	return items;
}

void DynamicObject::onDeath(){
	for (auto &item : generateLoot()){
		Engine::area.placeItem(item, location);
	}

	Engine::log.finishMessage(name + " dies.");
	Engine::area.killDynamicObject(*this);
}