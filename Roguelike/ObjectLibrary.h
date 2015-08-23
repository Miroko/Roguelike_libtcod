#pragma once
#include "Tile.h"
#include "OperatableObject.h"
#include "CreatureAi.h"
#include "WeaponAction.h"
#include "TemplateArmor.h"
#include "TemplateWeapon.h"
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
	std::unordered_map<std::string, std::shared_ptr<WeaponAction>> weaponActions;

	std::unordered_map<std::string, TemplateConsumable> consumableTemplates;
	std::unordered_map<std::string, TemplateWeapon> weaponTemplates;
	std::unordered_map<std::string, TemplateArmor> armorTemplates;
	std::unordered_map<std::string, TemplateCreatureBase> creatureBaseTemplates;
	std::unordered_map<std::string, TemplateCreaturePreset> creaturePresetTemplates;

	void init();

	ObjectLibrary(){}
};
