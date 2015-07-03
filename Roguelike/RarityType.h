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
	int modsPerItemMax;
	float prevalence;

	std::vector<RarityModCreature> creatureMods;
	std::vector<RarityModWeapon> weaponMods;
	std::vector<RarityModArmor> armorMods;
	std::vector<RarityModCreature*> getRandomCreatureMods();
	std::vector<RarityModWeapon*> getRandomWeaponMods();
	std::vector<RarityModArmor*> getRandomArmorMods();

	RarityType(
		std::string id,
		std::string name,
		float prevalence,
		float modRollChance,
		int modsPerItemMax,
		const TCODColor &color,
		std::vector<RarityModCreature> creatureMods,
		std::vector<RarityModWeapon> weaponMods,
		std::vector<RarityModArmor> armorMods) :
		id(id),
		name(name),
		prevalence(prevalence),
		modRollChance(modRollChance),
		modsPerItemMax(modsPerItemMax),
		color(color),
		creatureMods(creatureMods),
		weaponMods(weaponMods),
		armorMods(armorMods){};
};
