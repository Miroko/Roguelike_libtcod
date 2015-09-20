#pragma once
#include "RarityAffixAccessory.h"

class AccessoryAffixMagic : public RarityAffixAccessory
{
private:
	double magicModifier;

public:
	double getMagicModifier() override { return magicModifier; }
	std::string RarityAffix::getDescription(GameObject &ownerObject) override;

	AccessoryAffixMagic(std::string name, double magicModifier) :
		RarityAffixAccessory(name),
		magicModifier(magicModifier){}
};

