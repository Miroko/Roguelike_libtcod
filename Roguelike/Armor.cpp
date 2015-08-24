#include "Armor.h"
#include "RarityAffixArmor.h"
#include "Engine.h"
#include <algorithm>

std::string Armor::getStatistics(){
	return engine::string.defence(getDefence()) + " " + Equipment::getStatistics();
}

int Armor::getValue(){
	int value = Equipment::getValue();
	value += getDefence() * engine::valuePerDefence;
	return value;
}

int Armor::getDefence(){
	double totalDefence = (double)defence;
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->ARMOR_AFFIX)){
			RarityAffixArmor *armorAffix = static_cast<RarityAffixArmor*>(affix);
			totalDefence += defence * armorAffix->getDefenceModifier();
		}
	}
	totalDefence = 
		totalDefence * 
		(std::max(getDurabilityCurrent(), getDurabilityMax() * (1.0 - engine::durabilityMaxEffectOnDefencePercentage)) / getDurabilityMax());
	return (int)defence;
}