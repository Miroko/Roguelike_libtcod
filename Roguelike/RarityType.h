#pragma once
#include "libtcod.hpp"
#include "RarityAffixCreature.h"
#include "RarityAffixArmor.h"
#include "RarityAffixWeapon.h"
#include "RarityAffixConsumable.h"
#include <string>
#include <vector>
#include <memory>

class RarityType
{
public:
	std::string id;
	std::string name;
	TCODColor color;
	double prevalence;
	double improvementMultiplier;

	std::vector<std::shared_ptr<RarityAffixCreature>> creatureAffixesPre;
	std::vector<std::shared_ptr<RarityAffixArmor>> armorAffixesPre;
	std::vector<std::shared_ptr<RarityAffixWeapon>> weaponAffixesPre;
	std::vector<std::shared_ptr<RarityAffixConsumable>> consumableAffixesPre;

	std::vector<std::shared_ptr<RarityAffixCreature>> creatureAffixesPost;
	std::vector<std::shared_ptr<RarityAffixArmor>> armorAffixesPost;
	std::vector<std::shared_ptr<RarityAffixWeapon>> weaponAffixesPost;
	std::vector<std::shared_ptr<RarityAffixConsumable>> consumableAffixesPost;

	RarityType(std::string id, std::string name, TCODColor color, double prevalence, double improvementMultiplier) :
		id(id),
		name(name),
		color(color),
		prevalence(prevalence),
		improvementMultiplier(improvementMultiplier){}
	RarityType(){}
};
