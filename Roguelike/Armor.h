#pragma once
#include "Equipment.h"
#include "TemplateArmor.h"

class Armor : public Equipment
{
public:
	int defence;

	std::vector<RarityModArmor*> rarityMods;

	std::string getDescription();
	std::string getStatistics();
	int getValue();

	Armor(std::string name, Glyph glyph, float weight, Type type, int defence, RarityType &rarity, std::vector<RarityModArmor*> rarityMods) :
		Equipment(
		name,
		glyph,
		weight,
		type,
		rarity),
		defence(defence),
		rarityMods(rarityMods){};
};
