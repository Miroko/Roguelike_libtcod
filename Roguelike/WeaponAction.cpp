#include "WeaponAction.h"
#include "Creature.h"
#include "Weapon.h"
#include "Engine.h"

void WeaponAction::execute(Creature &executer, Weapon &actionObject, DynamicObject &target){
	engine::gui.log.addToMessage(executer.name + " " + logDescription + " " + target.name + " with " + actionObject.name + ". ");

	double accuracy = 
		engine::accuracyBasePercentage - 
		(actionObject.getWeight() + executer.inventory.getTotalEquippedWeight()) / 
		engine::carryWeightMax;
	accuracy += accuracy * accuracyModifier;

	if (engine::random.chance(accuracy)){
		double damage = actionObject.getDamage();
		damage += damage * damageModifier;
		target.onTakeDamage(executer, damage);

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
}
