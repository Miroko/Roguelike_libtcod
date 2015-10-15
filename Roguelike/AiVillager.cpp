#include "AiVillager.h"
#include "Creature.h"
#include "Engine.h"
#include "Village.h"
#include "Bed.h"
#include "Door.h"

void AiVillager::onTakeDamage(DynamicObject &attacker){
	if (attacker.type == Creature::CREATURE){
		combatModule.target = &attacker;
		if (combatModule.state != combatModule.FLEE){
			combatModule.state = combatModule.PURSUE_TARGET;
			currentState = COMBAT;
		}
	}
}

void AiVillager::onCreatureInFov(Creature &creature, int distance){
	if (combatModule.state == combatModule.FLEE) return;
	
	if (&creature == combatModule.target){
		combatModule.state = combatModule.PURSUE_TARGET;
	}
}

void AiVillager::onOperatableInFov(OperatableObject &operatable, int distance){
	if (currentState == IN_HOUSE && residentModule.residence->bounds.contains(operatable.location)){
		if (operatable.type == OperatableObject::BED){
			Bed &bed = static_cast<Bed&>(operatable);
			if (!bed.isInUse()){
				residentModule.bed = &bed;
			}
		}
	}
}

void AiVillager::nextToDestination(Point2D &location){

}

void AiVillager::onPathBlocked(Point2D &location){
	if (currentState == IN_HOUSE){
		return;
	}

	if (currentState == COMBAT){
		combatModule.state = combatModule.JAMMED;
		return;
	}
	
	if (currentState == VISIT_HOUSE){
		if (engine::random.chance(0.25)) calculatePath(houseToVisit->bounds.getCenterPoint());
		if (engine::random.chance(0.10)) currentState = WANDER;
		return;
	}
}

void AiVillager::onPathEnd(Point2D &location){

}

void AiVillager::initAi(Creature &owner, Area &area){
	CreatureAi::initAi(owner, area);
	combatModule.init(*this);
	residentModule.init(*this);
	operatedLastTurn = false;
	
	Village *village = static_cast<Village*>(&area);
	for (auto &house : village->houses){
		if (house.bounds.contains(owner.location)){
			residentModule.residence = &house;
			break;
		}
	}
	currentState = IN_HOUSE;
}

void AiVillager::update(){
	CreatureAi::update();
	if (currentState == COMBAT){
		combatModule.run();
	}
	else if (currentState == IN_HOUSE){
		residentModule.run();
		if (residentModule.currentState == residentModule.WANDER && engine::random.chance(0.003)){
			Village *village = static_cast<Village*>(area);
			houseToVisit = &village->houses.at(engine::random.generator->getInt(0, village->houses.size() - 1));
			calculatePath(houseToVisit->bounds.getCenterPoint());
			currentState = VISIT_HOUSE;
		}
	}
	else if (currentState == WANDER){
		owner->move(owner->location + engine::random.direction());
		if (engine::random.chance(0.30)){
			Village *village = static_cast<Village*>(area);
			houseToVisit = &village->houses.at(engine::random.generator->getInt(0, village->houses.size() - 1));
			calculatePath(houseToVisit->bounds.getCenterPoint());
			currentState = VISIT_HOUSE;
		}
	}
	else if (currentState == VISIT_HOUSE){
		Rectangle houseInside = houseToVisit->bounds;
		houseInside.shrink(2);
		if (houseInside.contains(owner->location)){
			//arrived to house
			residentModule.residence = houseToVisit;
			residentModule.currentState = residentModule.WANDER;
			currentState = IN_HOUSE;
		}
		if (path.size() == 0){
			calculatePath(houseToVisit->bounds.getCenterPoint());
		}
		else{
			//open/close door
			bool operated = false;
			if (!operatedLastTurn){
				int previousPathIndex = path.getCurrentIndex() - 1;
				int nextPathIndex = path.getCurrentIndex() + 1;
				if (previousPathIndex < 0) previousPathIndex = 0;
				if (nextPathIndex > path.size() - 1) nextPathIndex = path.size() - 1;
				Point2D previousPathLocation = path.getAt(previousPathIndex);
				Point2D nextPathLocation = path.getAt(nextPathIndex);
				if (area->areaContainers[nextPathLocation.x][nextPathLocation.y].operatableObject){
					if (area->areaContainers[nextPathLocation.x][nextPathLocation.y].operatableObject->isType(GameObject::DOOR)){
						Door &door = static_cast<Door&>(*area->areaContainers[nextPathLocation.x][nextPathLocation.y].operatableObject);
						door.operate(*owner);
						operated = true;
					}
				}
				else if (area->areaContainers[previousPathLocation.x][previousPathLocation.y].operatableObject){
					if (area->areaContainers[previousPathLocation.x][previousPathLocation.y].operatableObject->isType(GameObject::DOOR)){
						Door &door = static_cast<Door&>(*area->areaContainers[previousPathLocation.x][previousPathLocation.y].operatableObject);
						door.operate(*owner);
						operated = true;
					}
				}
			}
			if (!operated){
				moveOnPath();
			}
			//to not open/close door infinitely
			operatedLastTurn = operated;
		}
	}
}

std::shared_ptr<CreatureAi> AiVillager::copy(){
	return std::shared_ptr<CreatureAi>(new AiVillager(*this));
}