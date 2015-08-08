#pragma once
#include "Equipment.h"
#include "TemplateArmor.h"

class Armor : public Equipment
{
public:
	int defence;
	int limbsRequiredToEquip;

	std::vector<RarityModArmor*> rarityMods;

	std::string getStatistics();
	int getValue();

	Armor(std::string name, Glyph glyph, float weight, Type type, int limbsRequiredToHold, int limbsRequiredToEquip, int defence, RarityType &rarity, std::vector<RarityModArmor*> rarityMods) :
		Equipment(
		name,
		glyph,
		weight,
		type,
		rarity,
		limbsRequiredToHold),
		defence(defence),
		limbsRequiredToEquip(limbsRequiredToEquip),
		rarityMods(rarityMods){};
};
