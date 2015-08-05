#include "Creature.h"
#include "Engine.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Weapon.h"
#include "Armor.h"

void Creature::addEffect(std::shared_ptr<CreatureEffect> effect){
	effects.push_back(effect);
}
void Creature::damageMelee(Weapon &weapon, DynamicObject &target){
	//stamina cost
	int staminaCost = (int)(engine::objectLibrary.staminaBaseCost * (inventory.getTotalWeight() * 2 / engine::objectLibrary.maxWeight));
	if (staminaCurrent - staminaCost >= 0){
		staminaCurrent -= staminaCost;
		engine::gui.log.addToMessage(name + " attacks " + target.name + " with " + weapon.name + ". ");
		target.onTakeDamage(*this, weapon.damage);
		waitedLastTurn = false;
	}
	else{
		engine::gui.log.finishMessage(name + " is too exhausted to attack.");
		waitedLastTurn = true;
	}
}
void Creature::damageRanged(Weapon &weapon, DynamicObject &target){
	//stamina cost
	int staminaCost = (int)(engine::objectLibrary.staminaBaseCost * (inventory.getTotalWeight() * 2 / engine::objectLibrary.maxWeight));
	if (staminaCurrent - staminaCost >= 0){
		staminaCurrent -= staminaCost;
		engine::gui.log.addToMessage(name + " shoots " + target.name + " with " + weapon.name + ". ");
		target.onTakeDamage(*this, weapon.damage);
		waitedLastTurn = false;
	}
	else{
		engine::gui.log.finishMessage(name + " is too exhausted to shoot.");
		waitedLastTurn = true;
	}
}
void Creature::attack(DynamicObject &target){
	if (inventory.currentWeapon != nullptr && !target.isDead){
		switch (inventory.currentWeapon->type)
		{
		case Weapon::WEAPON_MELEE: damageMelee(*inventory.currentWeapon, target); break;
		case Weapon::WEAPON_RANGED: damageRanged(*inventory.currentWeapon, target); break;
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
		//stamina cost
		staminaCurrent -= amountAfterDefence / 4;
		if (staminaCurrent <= 0) staminaCurrent = 0;
		DynamicObject::onTakeDamage(attacker, amountAfterDefence);
	}
	else{
		engine::gui.log.finishMessage(attacker.name + " missed.");
	}
	ai->onTakeDamage(attacker);
}
void Creature::onDeath(){
	DynamicObject::onDeath();
	engine::objectFactory.generateLootDrop(*this);
}
bool Creature::move(Point2D &location){
	int staminaCost = (int)(engine::objectLibrary.staminaBaseCost * (inventory.getTotalWeight() / engine::objectLibrary.maxWeight) / 5);
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
	int staminaCost = (int)(engine::objectLibrary.staminaBaseCost * (inventory.getTotalWeight() / engine::objectLibrary.maxWeight) / 5);
	staminaCurrent -= staminaCost;
	waitedLastTurn = false;
}
void Creature::initAi(Area &area){
	ai->initAi(*this, area);
}
void Creature::update(){
	//ai
	ai->update();
	//regenerate stamina if waited
	if (waitedLastTurn) staminaCurrent += (int)(staminaMax * 0.05f);
	if (staminaCurrent >= staminaMax) staminaCurrent = staminaMax;
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

