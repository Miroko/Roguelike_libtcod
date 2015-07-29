#include "Weapon.h"
#include "Engine.h"

std::string Weapon::getStatistics(){
	return engine::string.damage(damage) + " " + Item::getStatistics();
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}