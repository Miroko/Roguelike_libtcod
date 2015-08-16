#pragma once
#include "RarityType.h"
#include "RarityMod.h"
#include <vector>

class Creature;
class RaritySystem
{
public:
	std::vector<RarityType> rarityTypes;

	RarityMod getCreatureMod(RarityType &rarityType);
	RarityMod getArmorMod(RarityType &rarityType);
	RarityMod getWeaponMod(RarityType &rarityType);
	RarityMod getConsumableMod(RarityType &rarityType);

	double getRarityRoll(Creature *fromCreature = nullptr);
	RarityType* getRarityType(double rarityRoll);
	RarityType* getRarityType(std::string id);

	void init();

	RaritySystem(){}
};

