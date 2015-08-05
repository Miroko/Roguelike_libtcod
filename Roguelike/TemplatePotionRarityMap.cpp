#include "TemplatePotionRarityMap.h"

TemplatePotion *TemplatePotionRarityMap::getPotionTemplate(std::string rarityId){
	auto retrived = rarityMappedPotionTemplates.find(rarityId);
	if (retrived != rarityMappedPotionTemplates.end()){
		return &retrived->second;
	}
	else return nullptr;
}