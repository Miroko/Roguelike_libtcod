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

	std::vector<std::shared_ptr<RarityAffix>> creatureAffixesPre;
	std::vector<std::shared_ptr<RarityAffix>> armorAffixesPre;
	std::vector<std::shared_ptr<RarityAffix>> weaponAffixesPre;
	std::vector<std::shared_ptr<RarityAffix>> consumableAffixesPre;

	std::vector<std::shared_ptr<RarityAffix>> creatureAffixesPost;
	std::vector<std::shared_ptr<RarityAffix>> armorAffixesPost;
	std::vector<std::shared_ptr<RarityAffix>> weaponAffixesPost;
	std::vector<std::shared_ptr<RarityAffix>> consumableAffixesPost;

	RarityType(std::string id, std::string name, TCODColor color, double prevalence, double improvementMultiplier) :
		id(id),
		name(name),
		color(color),
		prevalence(prevalence),
		improvementMultiplier(improvementMultiplier){}
	RarityType(){}
};
