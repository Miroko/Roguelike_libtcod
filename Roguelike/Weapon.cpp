#include "Weapon.h"
#include "RarityAffixWeapon.h"
#include "Engine.h"
#include <algorithm>

std::string Weapon::getStatistics(){
	return engine::string.damage(getDamageTotal()) + " " + Equipment::getStatistics();
}

int Weapon::getValue(){
	int value = Equipment::getValue();
	value += (int)(getDamageTotal() * engine::valuePerDamage);
	return value;
}

int Weapon::getDamageBase(){
	return damage;
}

int Weapon::getDamageTotal(){
	double damageTotal = (double)getDamageBase();
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->WEAPON_AFFIX)){
			RarityAffixWeapon *weaponAffix = static_cast<RarityAffixWeapon*>(affix);
			damageTotal += getDamageBase() * weaponAffix->getDamageModifier();
		}
	}

	//weight modifier
	damageTotal += engine::weightDamagePerKg * getWeightTotal();

	//durability modifier
	damageTotal = 
		damageTotal * 
		(std::max(getDurabilityCurrent(), getDurablilityMaxTotal() * (1.0 - engine::durabilityMaxEffectOnDamagePercentage)) / getDurablilityMaxTotal());

	return (int)damageTotal;
}

double Weapon::getAccuracyModifier(){
	double accuracyModifier = 1.0;
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->WEAPON_AFFIX)){
			RarityAffixWeapon &weaponAffix = static_cast<RarityAffixWeapon&>(*affix);
			accuracyModifier += weaponAffix.getAccuracyModifier();
		}
	}
	return accuracyModifier;
}

double Weapon::getStaminaCostModifier(){
	double staminaCostModifier = 1.0;
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->WEAPON_AFFIX)){
			RarityAffixWeapon &weaponAffix = static_cast<RarityAffixWeapon&>(*affix);
			staminaCostModifier += weaponAffix.getStaminaModifier();
		}
	}
	return staminaCostModifier;
}