#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"

void AiModuleCombat::run(){
	if (target != nullptr){
		if (owner->inFov(target->location)){
			owner->calculatePath(target->location);
			if (owner->moveOnPath()){
				owner->owner->attack(*target);
			}
		}
	}
}