#include "AccessoryAffixSkill.h"
#include "CreatureSkill.h"
#include "Accessory.h"
#include "Engine.h"

std::string AccessoryAffixSkill::getDescription(GameObject &ownerObject){
	Accessory &ownerAccessory = static_cast<Accessory&>(ownerObject);
	return skill.getDescription() + " " +
		engine::string.percentageValue(skillModifier * ownerAccessory.getSpellPowerBase());
}