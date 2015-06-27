#include "Weapon.h"
#include "String.h"

std::string Weapon::getStatistics(){
	return std::to_string(damage) + "d ";
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}