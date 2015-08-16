#include "Weapon.h"
#include "Engine.h"

std::string Weapon::getStatistics(){
	std::string statistics;
	if (type == GameObject::WEAPON_MELEE){
		statistics =
		engine::string.damage(getDamage()) + " " + 
		Item::getStatistics();
	}
	else if (type == GameObject::WEAPON_RANGED){
		statistics = 
		engine::string.damage(getDamage()) + " " +
		engine::string.range(range) + " " + 
		Item::getStatistics();
	}
	return statistics;
}

int Weapon::getValue(){
	int value = Item::getValue();
	value += (int)(getDamage() * engine::valuePerDamage);
	return value;
}

int Weapon::getDamage(){
	double totalDamage = (double)damage;
	for (auto &affix : rarityAffixes){
		RarityAffixWeapon *weaponAffix = static_cast<RarityAffixWeapon*>(affix);
		totalDamage += damage * weaponAffix->getDamageMultiplier();
	}
	return (int)totalDamage;
}