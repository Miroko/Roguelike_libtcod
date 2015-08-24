#include "Item.h"
#include "Engine.h"
#include "RarityAffixItem.h"

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
	return engine::string.weightKg(getWeight()) + " " + engine::string.currency(getValue());
}

int Item::getValue(){
	int value = (int)(getWeight() * engine::valuePerKg);
	return value;
}

double Item::getWeight(){
	double totalWeight = weightKg;
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->ITEM_AFFIX)){
			RarityAffixItem &itemAffix = static_cast<RarityAffixItem&>(*affix);
			totalWeight += weightKg * itemAffix.getWeightModifier();
		}
	}
	return totalWeight;
}