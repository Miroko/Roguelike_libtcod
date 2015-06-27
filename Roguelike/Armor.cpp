#include "Armor.h"

std::string Armor::getStatistics(){
	return std::to_string(defence) + "a ";
}

int Armor::getValue(){
	int value = Item::getValue();
	value += defence;
	return value;
}