#include "Consumable.h"

std::string Consumable::getDescription(){
	return Item::getDescription() + " c:" + std::to_string(getValue()); 
}

int Consumable::getValue(){
	int value = Item::getValue();
	for (auto &effect : effects){
		value += effect->getPotency();
	}
	return value;
}
