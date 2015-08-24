#pragma once
#include "RarityAffix.h"

class RarityAffixAccessory : public RarityAffix
{
public:
	std::string RarityAffix::getDescription();

	RarityAffixAccessory(std::string name) : 
		RarityAffix(name, ACCESSORY_AFFIX){}
};

