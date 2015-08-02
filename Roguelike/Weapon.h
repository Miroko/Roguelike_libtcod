#pragma once
#include "TemplateWeapon.h"
#include "Equipment.h"
#include "Engine.h"
#include <memory>

class Weapon : public Equipment
{
public:
	int damage;
	int range;

	std::vector<RarityModWeapon*> rarityMods;

	std::string getStatistics();
	int getValue();

	Weapon(std::string name, Glyph glyph, float weight, Type type, int damage, int range, RarityType &rarity, std::vector<RarityModWeapon*> rarityMods) :
		Equipment(
		name,
		glyph,
		weight,
		type,
		rarity),
		damage(damage),
		range(range),
		rarityMods(rarityMods){};
};

