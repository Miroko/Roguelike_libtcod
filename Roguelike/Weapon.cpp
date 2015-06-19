#include "Weapon.h"

std::string Weapon::getDescription(){
	return Item::getDescription() + " dm:" + std::to_string(damage) + " c:" + std::to_string(getValue());
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += damage;
	return value;
}