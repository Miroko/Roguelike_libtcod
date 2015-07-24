#pragma once
#include "libtcod.hpp"
#include "RarityModCreature.h"
#include "RarityModWeapon.h"
#include "RarityModArmor.h"
#include <string>
#include <vector>

class RarityType
{
public:
	std::string id;
	std::string name;
	const TCODColor &color;
	float modRollChance;
	int modsPerItem;
	float prevalence;
	float improvementMultiplier;

	std::vector<std::string> creatureMods;
	std::vector<std::string> weaponMods;
	std::vector<std::string> armorMods;
	std::vector<RarityModCreature*> getRandomCreatureMods();
	std::vector<RarityModWeapon*> getRandomWeaponMods();
	std::vector<RarityModArmor*> getRandomArmorMods();

	RarityType(
		std::string id,
		std::string name,
		float prevalence,
		float improvementMultiplier,
		float modRollChance,
		int modsPerItem,
		const TCODColor &color,
		std::vector<std::string> creatureMods,
		std::vector<std::string> armorMods,
		std::vector<std::string> weaponMods) :
		id(id),
		name(name),
		prevalence(prevalence),
		improvementMultiplier(improvementMultiplier),
		modRollChance(modRollChance),
		modsPerItem(modsPerItem),
		color(color),
		creatureMods(creatureMods),
		weaponMods(weaponMods),
		armorMods(armorMods){};
};
