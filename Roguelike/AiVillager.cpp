#include "AiVillager.h"
#include "Creature.h"
#include "Engine.h"
#include "Village.h"
#include "Bed.h"

void AiVillager::onTakeDamage(DynamicObject &attacker){
	if (attacker.type == Creature::CREATURE){
		combatModule.target = &attacker;
		currentState = COMBAT;
	}
}
void AiVillager::onCreatureInFov(Creature &creature, int distance){

}
void AiVillager::onOperatableInFov(OperatableObject &operatable, int distance){
	if (operatable.type == OperatableObject::BED){
		Bed &bed = static_cast<Bed&>(operatable);
		if (!bed.isOn){
			residentModule.bed = &bed;
		}
	}
}
void AiVillager::nextToDestination(Point2D &location){

}
void AiVillager::onPathBlocked(Point2D &location){
	if (currentState == VISIT_HOUSE){
		currentState = WANDER;
	}
}
void AiVillager::onPathEnd(Point2D &location){
	if (currentState == VISIT_HOUSE){
		currentState = WANDER;
	}
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
		if (residentModule.currentState == AiModuleResident::WANDER &&
			engine::random.generator->getFloat(0.0f, 1.0f) < 0.01f){
			Village *village = static_cast<Village*>(area);
			houseToVisit = &village->houses.at(engine::random.generator->getInt(0, village->houses.size() - 1));
			calculatePath(houseToVisit->bounds.getCenterPoint());
			currentState = VISIT_HOUSE;
		}
	}
	else if (currentState == WANDER){
		owner->move(owner->location + engine::random.direction());
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.60f){
			calculatePath(houseToVisit->bounds.getCenterPoint());
			currentState = VISIT_HOUSE;
		}
	}
	else if (currentState == VISIT_HOUSE){
		//open/close door	
		bool operated = false;
		if (!operatedLastTurn){
			if (pathMap->size() > 0){
				int previousPathIndex = currentPathIndex - 2;
				int nextPathIndex = currentPathIndex;
				Point2D previousPathLocation;
				Point2D nextPathLocation;
				if (previousPathIndex < 0) previousPathIndex = 0;
				if (nextPathIndex > pathMap->size() - 1) nextPathIndex = pathMap->size() - 1;
				pathMap->get(previousPathIndex, &previousPathLocation.x, &previousPathLocation.y);
				pathMap->get(nextPathIndex, &nextPathLocation.x, &nextPathLocation.y);
				for (auto &operatable : area->operatableObjects){
					if (operatable->type == OperatableObject::DOOR){
						if (operatable->location == nextPathLocation &&
							!operatable->isOn){
							operatable->on();
							operated = true;
						}
						else if (operatable->location == previousPathLocation &&
							operatable->isOn){
							operatable->off();
							operated = true;
						}
					}
				}
			}
		}
		if (!operated){
			moveOnPath();
		}
		operatedLastTurn = operated;

		//arrived to house
		Rectangle houseInside = houseToVisit->bounds;
		houseInside.shrink(2);
		if (houseInside.contains(owner->location)){
			residentModule.residence = houseToVisit;
			currentState = IN_HOUSE;
		}
	}
}

std::shared_ptr<CreatureAi> AiVillager::copy(){
	return std::shared_ptr<CreatureAi>(new AiVillager(*this));
}