#pragma once
#include "Tile.h"
#include "OperatableObject.h"
#include "CreatureAi.h"
#include "CreatureAction.h"
#include "CreatureSkill.h"
#include "CreatureEffect.h"
#include "TemplateArmor.h"
#include "TemplateWeapon.h"
#include "TemplateAccessory.h"
#include "TemplateConsumable.h"
#include "TemplateCreatureBase.h"
#include "TemplateCreaturePreset.h"
#include <unordered_map>
#include <memory>

class ObjectLibrary
{
public:
	std::unordered_map<std::string, std::shared_ptr<Tile>> tiles;
	std::unordered_map<std::string, std::shared_ptr<OperatableObject>> operatables;
	std::unordered_map<std::string, std::shared_ptr<CreatureAi>> ais;
	std::unordered_map<std::string, std::shared_ptr<CreatureAction>> creatureAction;
	std::unordered_map<std::string, std::shared_ptr<CreatureSkill>> creatureSkills;

	std::unordered_map<std::string, TemplateConsumable> consumableTemplates;
	std::unordered_map<std::string, TemplateWeapon> weaponTemplates;
	std::unordered_map<std::string, TemplateArmor> armorTemplates;
	std::unordered_map<std::string, TemplateAccessory> accessoryTemplates;
	std::unordered_map<std::string, TemplateCreatureBase> creatureBaseTemplates;
	std::unordered_map<std::string, TemplateCreaturePreset> creaturePresetTemplates;

	void init();

	ObjectLibrary(){}
};
