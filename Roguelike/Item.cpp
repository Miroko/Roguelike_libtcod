#include "Item.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}

std::string Item::getDescription(){
	return name;
}

int Item::getValue(){
	int value = 0;
	value += VALUE_PER_KG * weight;
	return value;
}