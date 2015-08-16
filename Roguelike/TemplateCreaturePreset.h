#pragma once
#include "Glyph.h"
#include <string>
#include <vector>

class TemplateCreaturePreset
{
public:
	std::string id;
	std::string name;
	Glyph glyph;
	double healthFromMax;
	std::string creatureBaseId;
	std::string aiId;
	std::vector<std::string> weaponIds;
	std::vector<std::string> armorIds;

	TemplateCreaturePreset(std::string id, std::string name, Glyph glyph, double healthFromMax, std::string creatureBaseId, std::string aiId, std::vector<std::string> weaponIds, std::vector<std::string> armorIds) :
		id(id),
		name(name),
		glyph(glyph),
		healthFromMax(healthFromMax),
		creatureBaseId(creatureBaseId),
		aiId(aiId),
		weaponIds(weaponIds),
		armorIds(armorIds){};
	TemplateCreaturePreset(){}
};

