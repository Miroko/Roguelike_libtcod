#pragma once
#include <string>
#include <vector>

class TemplateCreaturePreset
{
public:
	std::string id;
	std::string creatureTemplateId;
	std::vector<std::string> weaponIds;
	std::vector<std::string> armorIds;
	float health;

	TemplateCreaturePreset(std::string id, std::string creatureTemplateId, float health, std::vector<std::string> weaponIds,
		std::vector<std::string> armorIds) :
		id(id),
		creatureTemplateId(creatureTemplateId),
		weaponIds(weaponIds),
		armorIds(armorIds),
		health(health){};
};

