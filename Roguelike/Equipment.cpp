#include "Equipment.h"
#include "RarityAffixEquipment.h"
#include "Engine.h"

void Equipment::durabilityHit(double amount){
	durabilityCurrent -= amount;
	if (durabilityCurrent < 0) durabilityCurrent = 0;
}

bool Equipment::isBroken(){
	return durabilityCurrent == 0;
}

double Equipment::getDurabilityCurrent(){
	return durabilityCurrent;
}

double Equipment::getDurabilityMaxBase(){
	return durabilityMax;
}

double Equipment::getDurablilityMaxTotal(){
	double totalDurabilityMax = getDurabilityMaxBase();
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->EQUIPMENT_AFFIX)){
			RarityAffixEquipment &equipmentAffix = static_cast<RarityAffixEquipment&>(*affix);
			totalDurabilityMax += getDurabilityMaxBase() * equipmentAffix.getDurabilityModifier();
		}
	}
	return totalDurabilityMax;
}

int Equipment::getValue(){
	return Item::getValue() * (getDurabilityCurrent() / getDurablilityMaxTotal());
}

std::string Equipment::getStatistics(){
	return engine::string.durability(getDurabilityCurrent(), getDurablilityMaxTotal()) + " " + Item::getStatistics();
}