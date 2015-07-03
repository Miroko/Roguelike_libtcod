#include "Weapon.h"

std::string Weapon::getDescription(){
	return rarity.name + " " + name;
}

std::string Weapon::getStatistics(){
	return std::to_string(damage) + "d ";
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}