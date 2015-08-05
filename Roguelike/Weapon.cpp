#include "Weapon.h"
#include "Engine.h"

std::string Weapon::getStatistics(){
	std::string statistics;
	if (type == GameObject::WEAPON_MELEE){
		statistics =
		engine::string.damage(damage) + " " + 
		Item::getStatistics();
	}
	else if (type == GameObject::WEAPON_RANGED){
		statistics = 
		engine::string.damage(damage) + " " +
		engine::string.range(range) + " " + 
		Item::getStatistics();
	}
	return statistics;
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}