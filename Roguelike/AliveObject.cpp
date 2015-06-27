#include "AliveObject.h"
#include "Engine.h"
#include "Random.h"
#include "ObjectLibrary.h"

void AliveObject::damage(DynamicObject &target){
	target.onTakeDamage(*this, weapon->damage);
}

void AliveObject::attackMelee(DynamicObject &target){
	Engine::GUI.log.addToMessage(name + " attacks " + target.name + " with " + weapon->name + ". ");
	damage(target);
}

void AliveObject::attackRanged(DynamicObject &target){
	Engine::GUI.log.addToMessage(name + " shoots " + target.name + " with " + weapon->name + ". ");
	damage(target);
}

void AliveObject::onTakeDamage(DynamicObject &attacker, int amount){
	int amountAfterDefence = amount;
	int bodyPart = Random::generator.getInt(0, 3, 2);
	switch (bodyPart){
	case 3: if (armorHead != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorHead->defence, armorHead->defence); Engine::GUI.log.addToMessage("Head is hit. "); break;
	case 2: if (armorBody != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorBody->defence, armorBody->defence); Engine::GUI.log.addToMessage("Body is hit. "); break;
	case 1: if (armorHand != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorHand->defence, armorHand->defence); Engine::GUI.log.addToMessage("Arm is hit. "); break;
	case 0: if (armorLeg != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorLeg->defence, armorLeg->defence); Engine::GUI.log.addToMessage("Leg is hit. "); break;
	default: break;
	}
	if (amountAfterDefence < 0) amountAfterDefence = 0;

	ai.startCombat(attacker);

	DynamicObject::onTakeDamage(attacker, amountAfterDefence);
}

void AliveObject::update(){
	//Consumable effects
	if (!effects.empty()){
		effects.front()->apply(*this);
		effects.pop_front();
	}
	//Ai
	ai.update(*this);
}

void AliveObject::equipItem(Equipment &equipment){
	switch (equipment.type){
	case Item::WEAPON_MELEE: weapon = static_cast<Weapon*>(&equipment); break;
	case Item::WEAPON_RANGED: weapon = static_cast<Weapon*>(&equipment); break;
	case Item::ARMOR_HEAD: armorHead = static_cast<Armor*>(&equipment); break;
	case Item::ARMOR_BODY: armorBody = static_cast<Armor*>(&equipment); break;
	case Item::ARMOR_HAND: armorHand = static_cast<Armor*>(&equipment); break;
	case Item::ARMOR_LEG: armorLeg = static_cast<Armor*>(&equipment); break;
	default: break;
	}
}

void AliveObject::consume(Consumable &consumable){
	for (auto &effect : consumable.effects){
		for (int duration = effect->duration; duration > 0; duration--){
			effects.push_back(effect);
		}
	}
}
