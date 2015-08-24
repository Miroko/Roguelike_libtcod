#pragma once
#include "RarityAffix.h"

class RarityAffixItem : public RarityAffix
{
public:
	virtual double getWeightModifier(){ return 0.0; }

	RarityAffixItem(std::string name) :
		RarityAffix(name, ITEM_AFFIX){}
};

