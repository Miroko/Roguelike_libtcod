#pragma once
#include "RarityAffixItem.h"

class ItemAffixWeight : public RarityAffixItem
{
private:
	double percentageValue;

public:
	double getWeightModifier(){ return percentageValue; }
	std::string RarityAffix::getDescription(GameObject &ownerObject);

	ItemAffixWeight(std::string name, double percentageValue) :
		RarityAffixItem(name),
		percentageValue(percentageValue){}
};
