#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"
#include "Weapon.h"
#include "Engine.h"

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (owner->inFov(target.location)){
		owner->calculatePath(target.location);	
		if (target.location.distance(owner->owner->location) <= owner->owner->inventory.getWeapons().at(0)->range){
			owner->owner->attack(target);
		}
		else{
			owner->moveOnPath();
		}
	}	
	else{
		owner->moveOnPath();
	}
}
void AiModuleCombat::flee(){
	if (fleeLocation.undefined()){
		Rectangle fleeArea = Rectangle(owner->owner->location, 15);
		fleeLocation = owner->area->getNearestTile(engine::random.point(fleeArea), Tile::FLOOR);
		owner->calculatePath(fleeLocation);
	}
	if (owner->owner->location == fleeLocation){
		target = nullptr;
		fleeLocation = POINT_UNDEFINED;
		state = WAIT;
	}
	else owner->moveOnPath();
}
void AiModuleCombat::run(){
	if (state == WAIT){
		//wait
	}
	else if (state == JAMMED){
		owner->owner->move(owner->owner->location + engine::random.direction());
		state = PURSUE_TARGET;
	}
	else if (state == PURSUE_TARGET){
		if (target != nullptr){
			if (!owner->owner->inventory.getWeapons().empty()){
				pursueAndAttack(*target);
			}
			else{
				state = FLEE;
			}
		}
	}
	else if (state == FLEE){
		flee();
	}
}
