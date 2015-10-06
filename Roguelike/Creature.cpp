#include "Creature.h"
#include "Engine.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "RarityAffixAccessory.h"
#include <algorithm>

bool Creature::executeSkillAction(CreatureSkill &skill, double skillProficiency, CreatureAction &action, double actionProficiency, DynamicObject &target){
	bool executedAction = false;
	if (skill.isType(CreatureSkill::WEAPON)){
		//random action for both weapons
		for (auto &weapon : inventory.getEquippedWeapons()){
			auto &actions = weapon->skillUsed.getActionsAndProficiencies(1.0);
			auto &randomAction = actions.at(engine::random.generator->getInt(0, actions.size() - 1));
			if (randomAction.first->execute(*this, randomAction.second, *weapon, target)){
				executedAction = true;
			}
		}
	}
	else if (skill.isType(CreatureSkill::MAGIC)){
		if (action.execute(*this, actionProficiency, *this, target)){
			executedAction = true;
		}
	}
	if (executedAction) waitedLastTurn = false;
	else waitedLastTurn = true;
	return executedAction;
}

void Creature::takeDamage(DynamicObject &attacker, double amount){
	int amountAfterDefence = amount;
	auto &creatureLimb = limbs.at(engine::random.generator->getInt(0, limbs.size() - 1));
	if (engine::random.chance(creatureLimb.hitChance)){
		engine::gui.log.addToMessage(creatureLimb.name + " is hit. ");

		//defence
		amountAfterDefence -= inventory.getTotalDefence() / limbs.size();
		if (creatureLimb.currentArmor != nullptr){
			int armorDefence = creatureLimb.currentArmor->getDefenceTotal();
			amountAfterDefence -= engine::random.generator->getInt(0, armorDefence, armorDefence);

			if (!creatureLimb.currentArmor->isBroken()){
				double durabilityCost = engine::durabilityBaseCost;
				creatureLimb.currentArmor->durabilityHit(durabilityCost);
				if (creatureLimb.currentArmor->isBroken()){
					engine::gui.log.addMessage(creatureLimb.currentArmor->name + " has broken.");
				}
			}
		}
		if (amountAfterDefence < 0) amountAfterDefence = 0;

		//stamina cost from damage
		staminaHit(amountAfterDefence * engine::staminaCostFromDamageRation);

		DynamicObject::takeDamage(attacker, amountAfterDefence);
	}
	else{
		engine::gui.log.finishMessage(name + " evades.");
	}
	ai->onTakeDamage(attacker);
}
void Creature::addEffect(std::shared_ptr<CreatureEffect> effect){
	effects.push_back(effect);
}
void Creature::onDeath(){
	auto& lootDrop = engine::objectFactory.generateLootDrop(lootDropsFromMax, *rarityType);
	for (auto &loot : lootDrop){
		engine::areaHandler.getCurrentArea()->placeItem(loot, location);
	}
	DynamicObject::onDeath();
}
bool Creature::move(Point2D &location){
	int staminaCost = (int)(engine::staminaCostPerKgFromMove * inventory.getTotalWeight());
	if (staminaCurrent - staminaCost >= 0){
		//enough stamina to move
		return DynamicObject::move(location);
	}
	else{
		//only log player exhaustion
		if (engine::playerHandler.getPlayerCreature().get() == this){
			engine::gui.log.addMessage(name + " is too exhausted to move.");
		}
		waitedLastTurn = true;
		return true;
	}
}
void Creature::onMove(){
	DynamicObject::onMove();
	//on successful move decrease stamina
	staminaHit(engine::staminaCostPerKgFromMove * inventory.getTotalWeight());
	waitedLastTurn = false;
}
void Creature::initAi(Area &area){
	ai->initAi(*this, area);
}
void Creature::update(){
	//ai
	ai->update();
	//regenerate stamina
	if (waitedLastTurn) staminaHit(-engine::staminaBaseWaitRegen);
	else staminaHit(-engine::staminaBaseRegen);
	//apply effects
	auto &effectIterator = effects.begin();
	while (effectIterator != effects.end()){
		CreatureEffect *effect = effectIterator->get();
		effect->apply(*this);
		if (effect->duration <= 0){
			effectIterator = effects.erase(effectIterator);
		}
		else ++effectIterator;
	}
	//reset flags
	waitedLastTurn = true;
}

int Creature::getHealthCurrent(){
	return DynamicObject::getHealthCurrent();
}

int Creature::getHealthMax(){
	return DynamicObject::getHealthMax();
}

int Creature::getStaminaCurrent(){
	return staminaCurrent;
}

int Creature::getStaminaMax(){
	return staminaMax;
}

void Creature::staminaHit(int amount){
	staminaCurrent -= amount;
	if (staminaCurrent < 0) staminaCurrent = 0;
	else if (staminaCurrent > getStaminaMax()) staminaCurrent = getStaminaMax();
}

int Creature::getMagicCurrent(){
	return magicCurrent;
}

int Creature::getMagicMax(){
	double magicMaxTotal = (double)magicMax;
	for (auto &accessory : inventory.getAccessories()){
		for (auto &affix : accessory->rarityAffixes){
			if (affix->isType(RarityAffix::ACCESSORY_AFFIX)){
				RarityAffixAccessory &accessoryAffix = static_cast<RarityAffixAccessory&>(*affix);
				magicMaxTotal += engine::magicMax * accessoryAffix.getMagicModifier() * accessory->getSpellPowerBase();
			}
		}
	}
	return (int)magicMaxTotal;
}

void Creature::magicHit(int amount){
	magicCurrent -= amount;
	if (magicCurrent < 0) magicCurrent = 0;
	else if (magicCurrent > getMagicMax()) magicCurrent = getMagicMax();
}

double Creature::getSpellPowerModifier(){
	double spellPowerModifier = 0.0;
	for (auto &accessory : inventory.getAccessories()){
		spellPowerModifier += accessory->getSpellPowerTotal();
	}
	return spellPowerModifier;
}

std::vector<std::pair<CreatureSkill*, double>> Creature::getWeaponSkillsAndProfiencies(){
	std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies;
	for (auto &weapon : inventory.getEquippedWeapons()){
		bool newSkill = true;
		double profiency = 1.0;
		for (auto &skillAndProfiency : skillsAndProfiencies){
			if (skillAndProfiency.first == &weapon->skillUsed){
				newSkill = false;
				break;
			}
		}
		if (newSkill){
			skillsAndProfiencies.push_back(std::make_pair(&weapon->skillUsed, profiency));
		}
	}
	return skillsAndProfiencies;
}

std::vector<std::pair<CreatureSkill*, double>> Creature::getMagicSkillsAndProfiencies(){
	std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies;
	for (auto &accessory : inventory.getAccessories()){
		for (auto &affix : accessory->rarityAffixes){
			if (affix->isType(affix->ACCESSORY_AFFIX)){
				RarityAffixAccessory &accessoryAffix = static_cast<RarityAffixAccessory&>(*affix);
				CreatureSkill *affixSkill = accessoryAffix.getSkill();
				if (affixSkill){
					bool newSkill = true;
					double profiency = accessoryAffix.getProfiencyModifier() * accessory->getSpellPowerBase();
					for (auto &skillAndProfiency : skillsAndProfiencies){
						if (skillAndProfiency.first == affixSkill){
							skillAndProfiency.second += profiency;
							newSkill = false;
							break;
						}
					}
					if (newSkill){
						skillsAndProfiencies.push_back(std::make_pair(affixSkill, profiency));
					}
				}
			}
		}
	}
	return skillsAndProfiencies;
}

std::vector<std::pair<CreatureSkill*, double>> Creature::getCombatSkillsAndProficiencies(){
	auto &allSkillsAndProfiences = getWeaponSkillsAndProfiencies();
	auto &magicSkillsAndprofiences = getMagicSkillsAndProfiencies();
	allSkillsAndProfiences.insert(allSkillsAndProfiences.end(), magicSkillsAndprofiences.begin(), magicSkillsAndprofiences.end());
	return allSkillsAndProfiences;
}

void Creature::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	int offsetY = 0;
	//rarity
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
		TCOD_CENTER,
		rarityType->name);
	offsetY += 1;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
		TCOD_CENTER,
		getDescription());
	//health
	offsetY += 2;
	double percentageValue = ((double)getHealthCurrent() / (double)getHealthMax());
	TCODColor healthColor = TCODColor::lerp(Gui::HEALTH_MIN_COLOR, Gui::HEALTH_MAX_COLOR, percentageValue);
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		"Health");
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		healthColor,
		TCOD_RIGHT,
		engine::string.outOf(getHealthCurrent(), getHealthMax()));
	//stamina
	offsetY += 1;
	percentageValue = ((double)getStaminaCurrent() / (double)getStaminaMax());
	TCODColor staminaColor = TCODColor::lerp(Gui::STAMINA_MIN_COLOR, Gui::STAMINA_MAX_COLOR, percentageValue);
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		"Stamina");
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		staminaColor,
		TCOD_RIGHT,
		engine::string.outOf(getStaminaCurrent(), getStaminaMax()));
	//magic
	if (getMagicMax() > 0){
		offsetY += 1;
		percentageValue = ((double)getMagicCurrent() / (double)getMagicMax());
		TCODColor magicColor = TCODColor::lerp(Gui::MAGIC_MIN_COLOR, Gui::MAGIC_MAX_COLOR, percentageValue);
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Magic");
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			magicColor,
			TCOD_RIGHT,
			engine::string.outOf(getMagicCurrent(), getMagicMax()));
	}
	//items in hold
	auto &items = inventory.getHoldingItems();
	if (!items.empty()){
		offsetY += 2;
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Holding");
		for (auto &item : items){
			offsetY += 1;
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 0,
				item->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
				TCOD_LEFT,
				item->getDescription());
			if (item->isWeapon()){
				Weapon *weapon = static_cast<Weapon*>(item);
				std::string statistics = engine::string.damage(weapon->getDamageTotal());
				frame.printString(
					renderBounds.start.x, renderBounds.start.y + offsetY,
					renderBounds.getWidth(), 0,
					Gui::FRAME_FG,
					TCOD_RIGHT,
					statistics);
			}
		}
	}
	//armors
	auto &armors = inventory.getEquippedArmors();
	if (!armors.empty()){
		offsetY += 2;
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Armors");
		for (auto &armor : armors){
			offsetY += 1;
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 0,
				armor->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
				TCOD_LEFT,
				armor->getDescription());
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_RIGHT,
				engine::string.defence(armor->getDefenceTotal()));
		}
	}
	//accessories
	auto &accessories = inventory.getAccessories();
	if (!accessories.empty()){
		offsetY += 2;
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Accessories");
		for (auto &accessory : accessories){
			offsetY += 1;
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 0,
				accessory->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
				TCOD_LEFT,
				accessory->getDescription());
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_RIGHT,
				engine::string.spellPower(accessory->getSpellPowerTotal()));
		}
	}
	//effects
	if (!effects.empty()){
		offsetY += 2;
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Effects");
		for (auto &effect : effects){
			offsetY += 1;
			std::string effectString = effect->getDescription();
			int rowsNeededForString = frame.console->getHeightRect(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), 2,
				effectString.c_str());
			frame.printString(
				renderBounds.start.x, renderBounds.start.y + offsetY,
				renderBounds.getWidth(), rowsNeededForString,
				Gui::FRAME_FG, TCOD_LEFT,
				effectString);
			offsetY += rowsNeededForString - 1;
		}
	}
}
