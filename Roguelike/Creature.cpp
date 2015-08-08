#include "Creature.h"
#include "Engine.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Weapon.h"
#include "Armor.h"

void Creature::attack(DynamicObject &target){
	if (!target.isDead){
		auto &weapons = inventory.getWeapons();

		float weaponsWeight = 0;
		for (auto &weapon : weapons){
			weaponsWeight += weapon->weight;
		}

		int staminaCost = 
			(int)(engine::staminaCostPerKgFromAttack * 
			(inventory.getTotalEquippedWeight() + weaponsWeight));

		if (staminaCurrent - staminaCost >= 0){
			staminaCurrent -= staminaCost;
			for (auto &weapon : weapons){
				if (weapon->type == GameObject::WEAPON_MELEE){
					engine::gui.log.addToMessage(name + " attacks " + target.name + " with " + weapon->name + ". ");
				}
				else if (weapon->type == GameObject::WEAPON_RANGED){
					engine::gui.log.addToMessage(name + " shoots " + target.name + " with " + weapon->name + ". ");
				}
				float accuracy =
					1.0f -
					((inventory.getTotalEquippedWeight() + weapon->weight) / engine::carryWeightMax) /
					weapons.size();
				if (engine::random.chance(accuracy)){
					target.onTakeDamage(*this, weapon->damage);
				}
				else{
					engine::gui.log.finishMessage(name + " missed.");
				}
			}
			waitedLastTurn = false;
		}
		else{
			engine::gui.log.finishMessage(name + " is too exhausted to attack.");
			waitedLastTurn = true;
		}
	}
}
void Creature::onTakeDamage(DynamicObject &attacker, int amount){
	int amountAfterDefence = amount;
	auto &creatureLimb = limbs.at(engine::random.generator->getInt(0, limbs.size() - 1));
	if (engine::random.chance(creatureLimb.hitChance)){
		amountAfterDefence -= inventory.getTotalDefence() / limbs.size();
		if (creatureLimb.currentArmor != nullptr){
			amountAfterDefence -= engine::random.generator->getInt(0, creatureLimb.currentArmor->defence, creatureLimb.currentArmor->defence);
			if (amountAfterDefence < 0) amountAfterDefence = 0;
		}
		engine::gui.log.addToMessage(creatureLimb.name + " is hit. ");
		//stamina cost from damage
		staminaCurrent -= (int)(amountAfterDefence * engine::staminaCostFromDamageRation);
		if (staminaCurrent <= 0) staminaCurrent = 0;
		DynamicObject::onTakeDamage(attacker, amountAfterDefence);
	}
	else{
		engine::gui.log.finishMessage(attacker.name + " missed.");
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
	staminaCost = (int)(staminaCost * engine::areaHandler.getCurrentArea()->getTile(location)->staminaCostMultiplierForMove);
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
	//on successfull move decrease stamina
	int staminaCost = (int)(engine::staminaCostPerKgFromMove * inventory.getTotalWeight());
	staminaCost = (int)(staminaCost * engine::areaHandler.getCurrentArea()->getTile(location)->staminaCostMultiplierForMove);
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
	if (waitedLastTurn) staminaCurrent += engine::staminaBaseWaitRegen;
	else staminaCurrent += engine::staminaBaseRegen;
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

