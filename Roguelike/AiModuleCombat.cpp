#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"
#include "Weapon.h"
#include "MagicAction.h"
#include "WeaponAction.h"
#include "Engine.h"
#include <vector>

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (!target.isDead){
		if (owner->inFov(target.location)){
			owner->calculatePath(target.location);

			int distanceToTarget = target.location.distance(owner->owner->location);
			std::pair<CreatureSkill*, double> bestSkill;
			std::pair<CreatureAction*, double> bestAction;
			auto combatSkills = owner->owner->getCombatSkillsAndProficiencies();
			for (auto &skill : combatSkills){
				for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
					if (distanceToTarget <= action.first->range){
						//wait for stamina -> return
						//not enough magic -> continue to select other action
						Creature &user = *owner->owner;
						if (skill.first->isType(CreatureSkill::MAGIC)){
							MagicAction &magicAction = static_cast<MagicAction&>(*action.first);
							if (magicAction.getMagicCost(user) > user.getMagicCurrent()) continue;
							if (magicAction.getStaminaCost(user) > user.getStaminaCurrent()) return;
						}
						else if (skill.first->isType(CreatureSkill::WEAPON)){
							WeaponAction &weaponAction = static_cast<WeaponAction&>(*action.first);
							bool canUseOneOrMore = false;
							for (auto &weapon : user.inventory.getWeapons()){
								if (weaponAction.getStaminaCost(user, *weapon) <= user.getStaminaCurrent()){
									canUseOneOrMore = true;
									break;
								}
							}
							if (!canUseOneOrMore) return;
						}
						//assign skill and action to use
						if (bestSkill.first == nullptr){
							bestSkill = skill;
							bestAction = action;
						}
						else if (
							bestSkill.second < skill.second &&
						    bestAction.second < action.second){
							bestSkill = skill;
							bestAction = action;
						}
					}
				}
			}
			if (bestAction.first){
				owner->owner->executeSkillAction(*bestSkill.first, bestSkill.second, *bestAction.first, bestAction.second, target);
			}
			else{
				owner->moveOnPath();
			}
		}
		else{
			//target not in fov
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
