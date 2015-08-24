#include "WeaponAction.h"
#include "Creature.h"
#include "Weapon.h"
#include "RarityAffixWeapon.h"
#include "Engine.h"
#include <iostream>

bool WeaponAction::execute(Creature &executer, Weapon &actionObject, DynamicObject &target){
	//stamina
	double staminaCostBase = engine::staminaCostPerKgFromAttack * actionObject.getWeight();
	double staminaCostTotal = staminaCostBase + staminaCostBase * staminaCostModifier;

	//accuracy
	double accuracyBase = engine::accuracyBasePercentage - (actionObject.getWeight() + executer.inventory.getTotalEquippedWeight()) / engine::weightCarryMax;
	double accuracyTotal = accuracyBase + accuracyBase * accuracyModifier;

	//rarity affix effects
	for (auto &affix : actionObject.rarityAffixes){
		if (affix->isType(affix->WEAPON_AFFIX)){
			RarityAffixWeapon &weaponAffix = static_cast<RarityAffixWeapon&>(*affix);
			accuracyTotal += accuracyBase * weaponAffix.getAccuracyModifier();
			staminaCostTotal += staminaCostBase * weaponAffix.getStaminaModifier();
		}
	}
	
	//try to execute attack
	if (staminaCostTotal <= executer.staminaCurrent){
		executer.staminaCurrent -= staminaCostTotal;
		engine::gui.log.addToMessage(executer.name + " " + logDescription + " " + target.name + " with " + actionObject.name + ". ");
		if (engine::random.chance(accuracyTotal)){
			//damage
			double damageBase = actionObject.getDamage();
			double damageTotal = damageBase + damageBase * damageModifier;
			target.onTakeDamage(executer, damageTotal);

			if (!actionObject.isBroken()){
				double durabilityCost = engine::durabilityBaseCost;
				durabilityCost += durabilityCost * durabilityModifier;
				actionObject.durabilityHit(durabilityCost);
				if (actionObject.isBroken()){
					engine::gui.log.addMessage(actionObject.name + " has broken.");
				}
			}
		}
		else{
			engine::gui.log.finishMessage(executer.name + " misses.");
		}
		return true;
	}
	else{
		engine::gui.log.addMessage(executer.name + " is too exhausted to attack.");
		return false;
	}
}
