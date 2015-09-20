#pragma once
#include "RarityAffixAccessory.h"

class AccessoryAffixSpellPower : public RarityAffixAccessory
{
private:
	double spellPowerModifier;

public:
	double getSpellPowerModifier() override { return spellPowerModifier; }
	std::string RarityAffix::getDescription(GameObject &ownerObject) override;

	AccessoryAffixSpellPower(std::string name, double spellPowerModifier) :
		RarityAffixAccessory(name),
		spellPowerModifier(spellPowerModifier){}
};

