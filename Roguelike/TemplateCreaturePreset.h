#pragma once
#include "Glyph.h"
#include <string>
#include <vector>

class TemplateCreaturePreset
{
public:
	std::string id;
	std::string creatureTemplateId;
	std::string AiId;
	std::string name;
	Glyph glyph;
	std::vector<std::string> weaponIds;
	std::vector<std::string> armorIds;
	float health;

	TemplateCreaturePreset(std::string id, std::string creatureTemplateId, std::string AiId, std::string name, Glyph glyph, float health, std::vector<std::string> weaponIds, std::vector<std::string> armorIds) :
		id(id),
		creatureTemplateId(creatureTemplateId),
		AiId(AiId),
		name(name),
		glyph(glyph),
		weaponIds(weaponIds),
		armorIds(armorIds),
		health(health){};
};

