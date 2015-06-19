#include "Armor.h"

std::string Armor::getDescription(){
	return Item::getDescription() + " df:" + std::to_string(defence) + " c:" + std::to_string(getValue());
}

int Armor::getValue(){
	int value = Item::getValue();
	value += defence;
	return value;
}