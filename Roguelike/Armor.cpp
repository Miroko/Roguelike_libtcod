#include "Armor.h"
#include "RarityAffixArmor.h"
#include "Engine.h"
#include <algorithm>

std::string Armor::getStatistics(){
	return engine::string.defence(getDefence()) + " " + Equipment::getStatistics();
}

int Armor::getValue(){
	int value = Item::getValue();
	value += getDefence() * engine::valuePerDefence;
	return value;
}

int Armor::getDefence(){
	double totalDefence = (double)defence;
	for (auto &affix : rarityAffixes){
		RarityAffixArmor *armorAffix = static_cast<RarityAffixArmor*>(affix);
		totalDefence += defence * armorAffix->getDefenceMultiplier();
	}
	totalDefence = 
		totalDefence * 
		(std::max(durabilityCurrent, durabilityMax * (1.0 - engine::durabilityMaxEffectOnDefencePercentage)) / durabilityMax);
	return (int)defence;
}