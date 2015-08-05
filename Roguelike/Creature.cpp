#include "Creature.h"
#include "Engine.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Weapon.h"
#include "Armor.h"

int Creature::getTotalDefence(){
	int totalDefence = 0;
	for (auto &limb : limbs){
		if (limb.currentArmor != nullptr){
			totalDefence += limb.currentArmor->defence;
		}
	}
	return totalDefence;
}

void Creature::addEffect(std::shared_ptr<CreatureEffect> effect){
	effects.push_back(effect);
}
void Creature::damageMelee(Weapon &weapon, DynamicObject &target){
	engine::gui.log.addToMessage(name + " attacks " + target.name + " with " + weapon.name + ". ");
	target.onTakeDamage(*this, weapon.damage);
}
void Creature::damageRanged(Weapon &weapon, DynamicObject &target){
	engine::gui.log.addToMessage(name + " shoots " + target.name + " with " + weapon.name + ". ");
	target.onTakeDamage(*this, weapon.damage);
}
void Creature::attack(DynamicObject &target){
	if (inventory.currentWeapon != nullptr &&
		!target.isDead){
		switch (inventory.currentWeapon->type){
		case Weapon::WEAPON_MELEE: damageMelee(*inventory.currentWeapon, target); break;
		case Weapon::WEAPON_RANGED: damageRanged(*inventory.currentWeapon, target); break;
		}
	}
}
void Creature::onTakeDamage(DynamicObject &attacker, int amount){
	int amountAfterDefence = amount;
	auto &creatureLimb = limbs.at(engine::random.generator->getInt(0, limbs.size() - 1));
	if (engine::random.chance(creatureLimb.hitChance)){
		amountAfterDefence -= getTotalDefence() / limbs.size();
		if (creatureLimb.currentArmor != nullptr){
			amountAfterDefence -= engine::random.generator->getInt(0, creatureLimb.currentArmor->defence, creatureLimb.currentArmor->defence);
			if (amountAfterDefence < 0) amountAfterDefence = 0;
		}
		engine::gui.log.addToMessage(creatureLimb.name + " is hit. ");
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
void Creature::initAi(Area &area){
	ai->initAi(*this, area);
}
void Creature::update(){
	ai->update();
	//apply and decrease effect duration
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
}

