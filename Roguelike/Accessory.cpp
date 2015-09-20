#include "Accessory.h"
#include "RarityAffixAccessory.h"
#include "Engine.h"

int Accessory::getValue(){
	return Item::getValue();
}

std::string Accessory::getStatistics(){
	return 
		engine::string.spellPower(getSpellPowerTotal())  +
		" " + Item::getStatistics();
}

double Accessory::getSpellPowerBase(){
	return spellPower;
}

double Accessory::getSpellPowerTotal(){
	double spellPowerTotal = getSpellPowerBase();
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->ACCESSORY_AFFIX)){
			RarityAffixAccessory &accessoryAffix = static_cast<RarityAffixAccessory&>(*affix);
			spellPowerTotal += getSpellPowerBase() * accessoryAffix.getSpellPowerModifier();
		}
	}
	return spellPowerTotal;
}