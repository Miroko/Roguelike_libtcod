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
	engine::gui.log.addToMessage(name + " attacks " + target.name + " with " + weapon.name + ". ");
	target.onTakeDamage(*this, weapon.damage);
}
void Creature::damageRanged(Weapon &weapon, DynamicObject &target){
	engine::gui.log.addToMessage(name + " shoots " + target.name + " with " + weapon.name + ". ");
	target.onTakeDamage(*this, weapon.damage);
}
void Creature::attack(DynamicObject &target){
	if (inventory.currentWeapon != nullptr){
		switch (inventory.currentWeapon->type){
		case Weapon::WEAPON_MELEE: damageMelee(*inventory.currentWeapon, target); break;
		case Weapon::WEAPON_RANGED: damageRanged(*inventory.currentWeapon, target); break;
		}
	}
}
void Creature::onTakeDamage(DynamicObject &attacker, int amount){
	int amountAfterDefence = amount;
	for (auto &limb : limbs){
		if (limb.currentArmor != nullptr){
			if (engine::random.generator->getFloat(0.0, 1.0) < limb.hitChance){
				amountAfterDefence -= engine::random.generator->getInt(0, limb.currentArmor->defence, limb.currentArmor->defence);
				engine::gui.log.addToMessage(limb.name + " is hit. ");
				ai->onTakeDamage(attacker);
				break;
			}
		}
	}
	if (amountAfterDefence < 0) amountAfterDefence = 0;
	DynamicObject::onTakeDamage(attacker, amountAfterDefence);
}
void Creature::onDeath(){
	DynamicObject::onDeath();
	engine::objectFactory.generateLootDrop(*this);
}
void Creature::changeAi(std::shared_ptr<CreatureAi> newAi){
	ai = newAi;
}
void Creature::initAi(){
	ai->initAi(*this);
}
void Creature::update(){
	ai->update();
	if (!effects.empty()){
		effects.front()->apply(*this);
		effects.pop_front();
	}
}

