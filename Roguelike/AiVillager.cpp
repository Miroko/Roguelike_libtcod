#include "AiVillager.h"
#include "Creature.h"
#include "Engine.h"
#include "Village.h"

void AiVillager::onTakeDamage(DynamicObject &attacker){
	combatModule.target = dynamic_cast<Creature*>(&attacker);
	if (combatModule.target != nullptr){
		currentState = COMBAT;
	}
}
void AiVillager::onCreatureInFov(Creature &creature, int distance){

}
void AiVillager::onOperatableInFov(OperatableObject &operatable, int distance){
	if (currentState == VISIT_HOUSE){
		if (distance == 2){			
			for (int pathIndex = pathMap->size() - 1; pathIndex > 0; --pathIndex){
				Point2D pathPoint;
				pathMap->get(pathIndex, &pathPoint.x, &pathPoint.y);
				if (operatable.location == pathPoint){
					Door *door = dynamic_cast<Door*>(&operatable);
					if (door != nullptr){
						//door near on path
						if (door->isOn){
							door->off();
						}
						else{
							door->on();
						}
						return;
					}
				}
			}
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
	currentState = WANDER;
}

void AiVillager::update(){
	CreatureAi::update();
	if (currentState == COMBAT){
		combatModule.run();
	}
	else if (currentState == WANDER){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.001f){
			Village *village = static_cast<Village*>(area);
			AreaHouse randomHouse = village->houses.at(engine::random.generator->getInt(0, village->houses.size() - 1));
			calculatePath(randomHouse.bounds.getCenterPoint());
			currentState = VISIT_HOUSE;
		}
		else if (currentState == WANDER){
			if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.30f){
				owner->move(owner->location + engine::random.direction());
			}
		}
	}
	else if (currentState == VISIT_HOUSE){
		moveOnPath();
	}
}

std::shared_ptr<CreatureAi> AiVillager::copy(){
	return std::shared_ptr<CreatureAi>(new AiVillager(*this));
}