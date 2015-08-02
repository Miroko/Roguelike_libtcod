#include "Item.h"
#include "RarityType.h"
#include "Engine.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}

std::string Item::getDescription(){
	return name;
}

std::string Item::getStatistics(){
	return engine::string.currency(getValue()) + " " + engine::string.weight(weight);
}

int Item::getValue(){
	int value = 0;
	value += (int)(VALUE_WEIGHT_MULTIPLIER * weight);
	return value;
}