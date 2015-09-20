#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"
#include "Weapon.h"
#include "Engine.h"
#include <vector>

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (!target.isDead){
		if (owner->inFov(target.location)){
			owner->calculatePath(target.location);

			bool attacked = false;
			int distanceToTarget = target.location.distance(owner->owner->location);
			std::pair<CreatureSkill*, double> *bestSkill = nullptr;
			std::pair<CreatureAction*, double> *bestAction = nullptr;
			auto &combatSkills = owner->owner->getCombatSkillsAndProficiencies();
			for (auto &skill : combatSkills){
				for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
					if (distanceToTarget <= action.first->range){
						if (bestSkill == nullptr){
							bestSkill = &skill;
							bestAction = &action;
						}
						else if (
							bestSkill->second < skill.second &&
							bestAction->second < action.second){
							bestSkill = &skill;
							bestAction = &action;
						}
					}
				}
			}
			if (bestAction){
				owner->owner->executeSkillAction(*bestSkill->first, bestSkill->second, *bestAction->first, bestAction->second, target);
			}
			else{
				owner->moveOnPath();
			}
		}
		else{
			owner->moveOnPath();
		}
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
