#include "AiModuleCombat.h"
#include "CreatureAi.h"
#include "Creature.h"
#include "Weapon.h"
#include "MagicAction.h"
#include "WeaponAction.h"
#include "Engine.h"
#include <vector>

void AiModuleCombat::pursueAndAttack(DynamicObject &target){
	if (!&target) return;
	if (!owner->inFov(target.location)){
		if (owner->moveOnPath() == 0) state = JAMMED;
		return;
	}
	Creature &user = *owner->owner;
	std::vector<
		std::pair<
		std::pair<CreatureSkill*, double>,
		std::pair<CreatureAction*, double>
		>
	> validSkillActions;
	int distanceToTarget = target.location.distance(user.location);
	bool getCloserToTarget = false;
	//find valid magic actions
	for (auto &skill : user.getMagicSkillsAndProfiencies()){
		for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
			MagicAction &magicAction = static_cast<MagicAction&>(*action.first);
			if (magicAction.getMagicCost(user) > user.getMagicCurrent()) continue;
			if (magicAction.getStaminaCost(user) > user.getStaminaCurrent()) continue;
			if (magicAction.targetType == MagicAction::IN_RANGE){
				if (distanceToTarget > action.first->range){
					getCloserToTarget = true;
					continue;
				}
			}
			else if (magicAction.targetType == MagicAction::SELF){
				bool hasNeedToUse = false;
				for (auto &effect : magicAction.effects){
					switch (effect->statType)
					{
					case CreatureEffect::HEALTH:
						if (user.getHealthCurrent() + effect->getEffectAmountLeft() < user.getHealthMax()) hasNeedToUse = true;
						break;
					case CreatureEffect::STAMINA:
						if (user.getStaminaCurrent() + effect->getEffectAmountLeft() < user.getStaminaMax()) hasNeedToUse = true;
						break;
					case CreatureEffect::MAGIC:
						if (user.getMagicCurrent() + effect->getEffectAmountLeft() < user.getMagicMax()) hasNeedToUse = true;
						break;
					}
				}
				if (!hasNeedToUse) continue;
			}
			//valid action
			validSkillActions.push_back(std::make_pair(skill, action));
		}
	}
	//find valid weapon action
	for (auto &skill : user.getWeaponSkillsAndProfiencies()){
		for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
			WeaponAction &weaponAction = static_cast<WeaponAction&>(*action.first);
			for (auto &weapon : user.inventory.getEquippedWeapons()){
				if (&weapon->skillUsed == skill.first){
					if (weaponAction.getStaminaCost(user, *weapon) <= user.getStaminaCurrent()){
						if (distanceToTarget > action.first->range){
							getCloserToTarget = true;
							break;
						}
						else{
							//valid action
							validSkillActions.push_back(std::make_pair(skill, action));
							goto SELECT_ACTION;
						}
					}
				}
			}
		}
	}
	//select action to execute
	SELECT_ACTION:
	if (validSkillActions.empty()){
		if (getCloserToTarget){
			owner->calculatePath(target.location);
			owner->moveOnPath();
		}
		else state = FLEE;
	}
	else{
		std::pair <
			std::pair<CreatureSkill*, double>,
			std::pair<CreatureAction*, double>
		> randomAction = validSkillActions.at(engine::random.generator->getInt(0, validSkillActions.size() - 1));
		if (randomAction.second.first->targetType == CreatureAction::SELF){
			user.executeSkillAction(
				*randomAction.first.first,
				randomAction.first.second,
				*randomAction.second.first,
				randomAction.second.second,
				user);
		}
		else{
			user.executeSkillAction(
				*randomAction.first.first,
				randomAction.first.second,
				*randomAction.second.first,
				randomAction.second.second,
				target);
		}
	}	
}
void AiModuleCombat::flee(){
	if (fleeLocation.undefined()){
		Rectangle fleeArea = Rectangle(owner->owner->location, 4);
		fleeLocation = owner->area->getNearestTile(engine::random.point(fleeArea), Tile::FLOOR);
		owner->calculatePath(fleeLocation);
	}
	if (owner->owner->location == fleeLocation){
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
	}
	else if (state == PURSUE_TARGET){
		pursueAndAttack(*target);
	}
	else if (state == FLEE){
		flee();
	}
}
