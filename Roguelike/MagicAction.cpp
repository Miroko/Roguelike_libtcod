#include "MagicAction.h"
#include "Accessory.h"
#include "DynamicObject.h"
#include "Creature.h"
#include "Engine.h"
#include <algorithm>

bool MagicAction::execute(Creature &executer, double skillModifier, GameObject &actionObject, DynamicObject &target){

	//magic
	double magicCostBase = engine::magicCostBase;
	double magicCostTotal = magicCostBase * magicCostModifier;
	if (magicCostTotal > executer.getMagicCurrent()){
		engine::gui.log.addMessage(executer.name + " is too drained of magic to cast " + logDescription + ".");
		return false;
	}

	//stamina
	double staminaCostBase = engine::magicStaminaCostPerMagic * magicCostTotal;
	double staminaCostTotal = staminaCostBase +
		(staminaCostBase * staminaCostModifier);
	if (staminaCostTotal > executer.getStaminaCurrent()){
		engine::gui.log.addMessage(executer.name + " is too exhausted to cast " + logDescription + ".");
		return false;
	}

	//cast
	engine::gui.log.addMessage(executer.name + " casts " + logDescription + " to " + target.name + ". ");
	executer.magicHit((int)magicCostTotal);
	executer.staminaHit((int)staminaCostTotal);

	//add effects to target
	if (target.isCreature()){
		Creature &targetCreature = static_cast<Creature&>(target);
		for (auto &effect : effects){
			auto& newEffect = effect->clone();
			newEffect->modifier = newEffect->modifier * executer.getSpellPowerModifier();
			newEffect->duration = std::max((int)(newEffect->duration * executer.getSpellPowerModifier()), 1);
			targetCreature.addEffect(newEffect);
		}
		targetCreature.ai->onTakeDamage(executer);
	}

	return true;
}
