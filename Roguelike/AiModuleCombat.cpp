#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (owner->inFov(target.location)){
		owner->calculatePath(target.location, true);
		if (owner->moveOnPath() == 1){
			owner->owner->attack(target);
		}
	}
}
void AiModuleCombat::run(){
	if (target != nullptr){
		pursueAndAttack(*target);
	}
}
