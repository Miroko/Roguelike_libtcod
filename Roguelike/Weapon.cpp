#include "Weapon.h"

std::string Weapon::getDescription(){
	return Item::getDescription() + " d:" + std::to_string(damage) + " v:" + std::to_string(getValue());
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}