
/*
#include "AliveObject.h"
#include "Engine.h"

void AliveObject::addEffect(std::shared_ptr<CreatureEffect> effect){
	effects.push_back(effect);
}
void AliveObject::damageMelee(std::shared_ptr<Weapon> weapon, std::shared_ptr<DynamicObject> target){
	engine::gui.log.addToMessage(name + " attacks " + target->name + " with " + weapon->name + ". ");
	target->onTakeDamage(*this, weapon->damage);
}
void AliveObject::damageRanged(std::shared_ptr<Weapon> weapon, std::shared_ptr<DynamicObject> target){
	engine::gui.log.addToMessage(name + " shoots " + target->name + " with " + weapon->name + ". ");
	target->onTakeDamage(*this, weapon->damage);
}
void AliveObject::onTakeDamage(DynamicObject &attacker, int amount){
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
void AliveObject::initAi(){
	ai->initAi();
}
void AliveObject::update(){
	ai->update();
	if (!effects.empty()){
		effects.front()->apply(*this);
		effects.pop_front();
	}
}
*/