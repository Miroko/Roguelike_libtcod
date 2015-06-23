#include "AliveObject.h"
#include "Engine.h"
#include "Random.h"

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
	//Effects
	auto &effect = effects.items.begin();
	while (effect != effects.items.end()){
		if (effect->get()->duration <= 0){
			effect = effects.items.erase(effect);
		}
		else{
			effect->get()->duration--;
			effect->get()->update(*this);
			++effect;
		}
	}
	ai.update(*this);
}

void AliveObject::equip(std::shared_ptr<Item> equipment){
	switch (equipment->type){
	case Item::WEAPON_MELEE: weapon = std::static_pointer_cast<Weapon>(equipment); break;
	case Item::WEAPON_RANGED: weapon = std::static_pointer_cast<Weapon>(equipment); break;
	case Item::ARMOR_HEAD: armorHead = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_BODY: armorBody = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_HAND: armorHand = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_LEG: armorLeg = std::static_pointer_cast<Armor>(equipment); break;
	default: break;
	}
}

void AliveObject::consume(std::shared_ptr<Item> consumable){
	Consumable *c = static_cast<Consumable*>(consumable.get());
	for (auto &effect : c->effects){
		switch (effect->type){
		case AliveObjectEffect::HEAL: addEffect(AliveObjectEffect::newEffect(std::static_pointer_cast<Heal>(effect))); break;
		default: break;
		}
	}
}

void AliveObject::addEffect(std::shared_ptr<AliveObjectEffect> effect){
	effects.add(effect);
}