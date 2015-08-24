#include "Weapon.h"
#include "RarityAffixWeapon.h"
#include "Engine.h"
#include <algorithm>

std::string Weapon::getStatistics(){
	std::string statistics;
	if (type == GameObject::WEAPON_MELEE){
		statistics =
		engine::string.damage(getDamage()) + " " + 
		Equipment::getStatistics();
	}
	else if (type == GameObject::WEAPON_RANGED){
		statistics = 
		engine::string.damage(getDamage()) + " " +
		engine::string.range(range) + " " + 
		Equipment::getStatistics();
	}
	return statistics;
}

int Weapon::getValue(){
	int value = Equipment::getValue();
	value += (int)(getDamage() * engine::valuePerDamage);
	return value;
}

int Weapon::getDamage(){
	double totalDamage = (double)damage;
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->WEAPON_AFFIX)){
			RarityAffixWeapon *weaponAffix = static_cast<RarityAffixWeapon*>(affix);
			totalDamage += damage * weaponAffix->getDamageModifier();
		}
	}
	totalDamage += engine::weightDamagePerKg * getWeight();

	totalDamage = 
		totalDamage * 
		(std::max(getDurabilityCurrent(), getDurabilityMax() * (1.0 - engine::durabilityMaxEffectOnDamagePercentage)) / getDurabilityMax());
	return (int)totalDamage;
}