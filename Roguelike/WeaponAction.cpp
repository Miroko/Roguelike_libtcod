#include "WeaponAction.h"
#include "Creature.h"
#include "Weapon.h"
#include "RarityAffixWeapon.h"
#include "Engine.h"

bool WeaponAction::execute(Creature &executer, double skillModifier, GameObject &actionObject, DynamicObject &target){
	if (actionObject.isWeapon()){
		Weapon &actionWeapon = static_cast<Weapon&>(actionObject);

		//stamina
		double staminaCostBase = engine::staminaCostPerKgFromAttack * actionWeapon.getWeightTotal();
		double staminaCostTotal = staminaCostBase +
			(staminaCostBase * staminaCostModifier) *
			(staminaCostBase * actionWeapon.getStaminaCostModifier());
		if (staminaCostTotal > executer.getStaminaCurrent()){
			engine::gui.log.addMessage(executer.name + " is too exhausted to " + logDescription + " with " + actionObject.name + ".");
			return false;
		}

		//accuracy
		double accuracyBase = engine::accuracyBasePercentage - (executer.inventory.getTotalEquippedWeight() / engine::weightCarryMax);
		double accuracyTotal = accuracyBase +
			(accuracyBase * accuracyModifier) *
			(accuracyBase * actionWeapon.getAccuracyModifier());
		if (!engine::random.chance(accuracyTotal)){
			engine::gui.log.finishMessage(executer.name + " misses.");
			return true;
		}

		//attack
		engine::gui.log.addToMessage(executer.name + " " + logDescription + " " + target.name + " with " + actionObject.name + ". ");
		executer.staminaHit((int)staminaCostTotal);

		//damage
		double damageBase = actionWeapon.getDamageTotal();
		double damageTotal = damageBase + damageBase * damageModifier;
		target.takeDamage(executer, damageTotal);

		//visual effect
		CreatureAction::execute(executer, profiencyModifier, actionObject, target);

		//durability
		if (!actionWeapon.isBroken()){
			double durabilityCost = engine::durabilityBaseCost;
			durabilityCost += durabilityCost * durabilityModifier;
			actionWeapon.durabilityHit(durabilityCost);
			if (actionWeapon.isBroken()){
				engine::gui.log.addMessage(actionObject.name + " has broken.");
			}
		}

		return true;
	}
	else{
		throw "actionObject != weapon";
	}
}
