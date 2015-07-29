#include "Armor.h"
#include "Engine.h"

std::string Armor::getStatistics(){
	return engine::string.defence(defence) + " " + Item::getStatistics();
}

int Armor::getValue(){
	int value = Item::getValue();
	value += defence;
	return value;
}