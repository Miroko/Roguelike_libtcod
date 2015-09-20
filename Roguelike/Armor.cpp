#include "Armor.h"
#include "RarityAffixArmor.h"
#include "Engine.h"
#include <algorithm>

std::string Armor::getStatistics(){
	return engine::string.defence(getDefenceTotal()) + " " + Equipment::getStatistics();
}

int Armor::getValue(){
	int value = Equipment::getValue();
	value += getDefenceTotal() * engine::valuePerDefence;
	return value;
}

int Armor::getDefenceBase(){
	return defence;
}

int Armor::getDefenceTotal(){
	double totalDefence = (double)getDefenceBase();
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->ARMOR_AFFIX)){
			RarityAffixArmor *armorAffix = static_cast<RarityAffixArmor*>(affix);
			totalDefence += getDefenceBase() * armorAffix->getDefenceModifier();
		}
	}

	//durability modifier
	totalDefence = 
		totalDefence * 
		(std::max(getDurabilityCurrent(), getDurablilityMaxTotal() * (1.0 - engine::durabilityMaxEffectOnDefencePercentage)) / getDurablilityMaxTotal());

	return (int)totalDefence;
}