#include "WeaponAction.h"
#include "Creature.h"
#include "Weapon.h"
#include "RarityAffixWeapon.h"
#include "Engine.h"

int WeaponAction::getStaminaCost(Creature &user, Weapon &actionWeapon){
	return
		(int)
		(engine::staminaCostPerKgFromAttack *
		actionWeapon.getWeightTotal() *
		actionWeapon.getStaminaCostModifier() *
		staminaCostModifier);
}

double WeaponAction::getAccuracy(Creature &user, Weapon &actionWeapon){
	return
		(double)
		(engine::accuracyBasePercentage - (user.inventory.getTotalEquippedWeight() / engine::weightCarryMax)) *
		actionWeapon.getAccuracyModifier() *
		accuracyModifier;
}

int WeaponAction::getDamage(Creature &user, Weapon &actionWeapon){
	return
		(int)
		(actionWeapon.getDamageTotal() * damageModifier);
}

double WeaponAction::getDurabilityCost(Creature &user, Weapon &actionWeapon){
	return
		(double)
		(engine::durabilityBaseCost * durabilityModifier);
}

bool WeaponAction::execute(Creature &executer, double actionProficiency, GameObject &actionObject, DynamicObject &target){
	if (actionObject.isWeapon()){
		Weapon &actionWeapon = static_cast<Weapon&>(actionObject);

		//stamina
		if (getStaminaCost(executer, actionWeapon) > executer.getStaminaCurrent()){
			engine::gui.log.addMessage(executer.name + " is too exhausted to " + logDescription + " with " + actionObject.name + ".");
			return false;
		}
		executer.staminaHit(getStaminaCost(executer, actionWeapon));

		//attack
		engine::gui.log.addToMessage(executer.name + " " + logDescription + " " + engine::string.targetName(executer, target) + " with " + actionObject.name + ". ");

		//accuracy
		if (!engine::random.chance(getAccuracy(executer, actionWeapon))){
			engine::gui.log.finishMessage(executer.name + " misses.");
			return true;
		}

		//damage
		target.takeDamage(executer, getDamage(executer, actionWeapon));

		//visual effect
		CreatureAction::execute(executer, profiencyModifier, actionObject, target);

		//durability
		if (!actionWeapon.isBroken()){
			actionWeapon.durabilityHit(getDurabilityCost(executer, actionWeapon));
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
