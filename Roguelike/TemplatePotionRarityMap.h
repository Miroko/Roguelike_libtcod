#pragma once
#include "TemplatePotion.h"
#include <unordered_map>

class TemplatePotionRarityMap
{
public:
	std::unordered_map<std::string, TemplatePotion> rarityMappedPotionTemplates;

	TemplatePotion *getPotionTemplate(std::string rarityId);

	TemplatePotionRarityMap(std::unordered_map<std::string, TemplatePotion> rarityMappedPotionTemplates) :
		rarityMappedPotionTemplates(rarityMappedPotionTemplates){};
};

