#include "Creature.h"
#include "Engine.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Weapon.h"
#include "Armor.h"

void Creature::attack(std::vector<std::pair<Weapon*, WeaponAction*>> &weaponActions, DynamicObject &target){
	double totalStaminaCost = 0;
	for (auto &weaponAction : weaponActions){
		double staminaCost =
			engine::staminaCostPerKgFromAttack *
			weaponAction.first->getWeight();
		staminaCost += staminaCost * weaponAction.second->staminaCostModifier;
		totalStaminaCost += staminaCost;
	}
	if (totalStaminaCost <= staminaCurrent){
		staminaCurrent -= totalStaminaCost;
		for (auto &weaponAction : weaponActions){
			weaponAction.second->execute(*this, *weaponAction.first, target);
		}
		waitedLastTurn = false;
	}
	else{
		engine::gui.log.addMessage(name + " is too exhausted to attack.");
		waitedLastTurn = true;
	}
}

void Creature::onTakeDamage(DynamicObject &attacker, double amount){
	int amountAfterDefence = amount;
	auto &creatureLimb = limbs.at(engine::random.generator->getInt(0, limbs.size() - 1));
	if (engine::random.chance(creatureLimb.hitChance)){
		amountAfterDefence -= inventory.getTotalDefence() / limbs.size();
		if (creatureLimb.currentArmor != nullptr){
			int armorDefence = creatureLimb.currentArmor->getDefence();
			amountAfterDefence -= engine::random.generator->getInt(0, armorDefence, armorDefence);
			if (amountAfterDefence < 0) amountAfterDefence = 0;

			if (!creatureLimb.currentArmor->isBroken()){
				double durabilityCost = engine::durabilityBaseCost;
				creatureLimb.currentArmor->durabilityHit(durabilityCost);
				if (creatureLimb.currentArmor->isBroken()){
					engine::gui.log.addMessage(creatureLimb.currentArmor->name + " has broken.");
				}
			}
		}
		engine::gui.log.addToMessage(creatureLimb.name + " is hit. ");
		//stamina cost from damage
		staminaCurrent -= (int)(amountAfterDefence * engine::staminaCostFromDamageRation);
		if (staminaCurrent <= 0) staminaCurrent = 0;
		DynamicObject::onTakeDamage(attacker, amountAfterDefence);
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
	DynamicObject::onDeath();
	engine::objectFactory.generateLootDrop(*this);
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
	int staminaCost = (int)(engine::staminaCostPerKgFromMove * inventory.getTotalWeight());
	staminaCurrent -= staminaCost;
	waitedLastTurn = false;
}
void Creature::initAi(Area &area){
	ai->initAi(*this, area);
}
void Creature::update(){
	//ai
	ai->update();
	//regenerate stamina
	if (waitedLastTurn) staminaCurrent += (int)engine::staminaBaseWaitRegen;
	else staminaCurrent += (int)engine::staminaBaseRegen;
	if (staminaCurrent > staminaMax) staminaCurrent = staminaMax;
	//apply effects and decrease duration
	auto &effectIterator = effects.begin();
	while (effectIterator != effects.end()){
		CreatureEffect *effect = effectIterator->get();
		effect->apply(*this);
		effect->duration--;
		if (effect->duration <= 0){
			effectIterator = effects.erase(effectIterator);
		}
		else ++effectIterator;
	}
	//reset flags
	waitedLastTurn = true;
}

