#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"
#include "Weapon.h"

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (owner->inFov(target.location)){
		owner->calculatePath(target.location, true);		
		if (owner->owner->inventory.currentWeapon->type == Weapon::WEAPON_MELEE){
			if (target.location.distance(owner->owner->location) == 1){
				owner->owner->attack(target);
			}
			else{
				owner->moveOnPath();
			}
		}
		else if (owner->owner->inventory.currentWeapon->type == Weapon::WEAPON_RANGED){
			if (target.location.distance(owner->owner->location) <= 6){
				owner->owner->attack(target);
			}
			else{
				owner->moveOnPath();
			}
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
	if (target != nullptr){
		if (owner->owner->inventory.currentWeapon != nullptr){
			state = PURSUE;
		}
		else{
			state = FLEE;
		}
	}
	if (state == WAIT){
		//wait
	}
	else if (state == PURSUE){
		pursueAndAttack(*target);
	}
	else if (state = FLEE){
		flee();
	}
}
