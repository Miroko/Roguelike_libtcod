#pragma once
#include "RarityAffixItem.h"

class ItemAffixWeight : public RarityAffixItem
{
public:
	double percentage;
	double getWeightModifier(){ return percentage; }
	std::string RarityAffix::getDescription();

	ItemAffixWeight(std::string name, double percentage) :
		RarityAffixItem(name),
		percentage(percentage){}
};
