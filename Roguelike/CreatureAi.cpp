#include "CreatureAi.h"
#include "Area.h"
#include "Engine.h"

void CreatureAi::calculateFov(){
	fov.compute(owner->location);
}

void CreatureAi::calculatePath(Point2D &location){
	path = area->pathFinder.computePath(owner->location, location, [&](Point2D& toLocation){
		auto &areaContainer = area->areaContainers[toLocation.x][toLocation.y];
		int movementCost = areaContainer.tile->getMovementCost();
		if (movementCost == INT_MAX) return INT_MAX;
		if (toLocation == location) return movementCost; //able to find path to unpassable object
		if (areaContainer.creature) return 1 + movementCost * 2; //avoid creatures but able to path through them
		if (areaContainer.operatableObject){
			if (!areaContainer.operatableObject->isPassable(*owner)){
				if (areaContainer.operatableObject->isType(GameObject::DOOR)){
					return movementCost; //able to path through doors
				}
				else return INT_MAX;
			}
		}
		return movementCost;
	});
}

int CreatureAi::moveOnPath(){
	if (path.size() > 0){
		if (owner->location == path.getDestination()) return path.remainingDistance();

		path.next();
		Point2D &nextLocation = path.getCurrentLocation();
		if (!owner->move(nextLocation)){
			onPathBlocked(nextLocation);
			path.previous();
		}
	}
	return path.remainingDistance();
}

void CreatureAi::onTakeDamage(DynamicObject &attacker){
	
}

void CreatureAi::onCreatureInFov(Creature &creature, int distance){

}

void CreatureAi::onOperatableInFov(OperatableObject &operatable, int distance){

}

void CreatureAi::nextToDestination(Point2D &location){

}

void CreatureAi::onPathBlocked(Point2D &location){

}

void CreatureAi::onPathEnd(Point2D &location){

}

bool CreatureAi::inFov(Point2D &location){
	return fov.getLuminosity(owner->location, location) > 0;
}

void CreatureAi::initAi(Creature &owner, Area &area){
	this->owner = &owner;
	this->area = &area;
	calculateFov();
}

void CreatureAi::update(){
	calculateFov();
	for (auto &dynamicObject : area->dynamicObjectsAlive){
		if (inFov(dynamicObject->location)){
			if (dynamicObject->isCreature()){
				if (dynamicObject.get() == owner) continue;
				Creature &creature = static_cast<Creature&>(*dynamicObject);
				onCreatureInFov(creature, creature.location.distance(owner->location));
			}
			else if (dynamicObject->isOperatable()){
				OperatableObject &operatable = static_cast<OperatableObject&>(*dynamicObject);
				onOperatableInFov(operatable, operatable.location.distance(owner->location));
			}
		}
	}
}