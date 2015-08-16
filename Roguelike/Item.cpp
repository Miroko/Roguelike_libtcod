#include "Item.h"
#include "Engine.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}

std::string Item::getDescription(){
	std::string description = name;
	RarityAffix* affixPre = getAffixPre();
	if (affixPre != nullptr) description.insert(0, affixPre->name + " ");
	RarityAffix* affixPost = getAffixPost();
	if (affixPost != nullptr) description.append(" of " + affixPost->name);
	return description;
}

std::string Item::getStatistics(){
	return engine::string.currency(getValue()) + " " + engine::string.weightKg(weightKg);
}

int Item::getValue(){
	int value = (int)(getWeight() * engine::valuePerKg);
	return value;
}

double Item::getWeight(){
	return weightKg;
}