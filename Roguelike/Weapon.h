#pragma once
#include "TemplateWeapon.h"
#include "Equipment.h"
#include "Engine.h"
#include <memory>

class Weapon : public Equipment
{
public:
	int damage;

	std::vector<RarityModWeapon*> rarityMods;

	std::string getStatistics();
	int getValue();

	Weapon(std::string name, Glyph glyph, float weight, Type type, int damage, RarityType &rarity, std::vector<RarityModWeapon*> rarityMods) :
		Equipment(
		name,
		glyph,
		weight,
		type,
		rarity),
		damage(damage),
		rarityMods(rarityMods){};
};

