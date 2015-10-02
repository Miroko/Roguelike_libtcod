#include "CreatureAi.h"
#include "Area.h"
#include "Engine.h"

float CreatureAi::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	CreatureAi *thisObject = static_cast<CreatureAi*>(userData);
	auto &areaContainer = thisObject->area->areaContainers[xTo][yTo];
	float walkCost = (float)areaContainer.tile->walkCost;
	if (walkCost > 0){ // walkcost <= 0 == unwalkable
		//able to find path to unpassable object eg. creature, operatable
		Point2D destination;
		thisObject->pathMap->getDestination(&destination.x, &destination.y);
		if (xTo == destination.x &&	yTo == destination.y) return walkCost;
		//--------
		if (areaContainer.creature){
			return 0;
		}
		if (areaContainer.operatableObject){
			if (!areaContainer.operatableObject->isPassable(*thisObject->owner)){
				if (areaContainer.operatableObject->isType(GameObject::DOOR)){
					//able to path through doors
					return walkCost;
				}
				else{
					return 0;
				}
			}
		}
	}
	return walkCost;
}

void CreatureAi::createPathMap(){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		area->getBounds().getWidth(),
		area->getBounds().getHeight(),
		new PathCostCallback(),
		this));
}

void CreatureAi::calculateFov(){
	fov.compute(owner->location);
}

void CreatureAi::calculatePath(Point2D &location){
	pathMap->compute(owner->location.x, owner->location.y, location.x, location.y);
	currentPathIndex = 0;
}

int CreatureAi::moveOnPath(){
	if (pathMap->size() == 0) return 0;
	if (currentPathIndex == pathMap->size()) return 0;

	Point2D newLocation;
	int distance = pathMap->size() - currentPathIndex;
	pathMap->get(currentPathIndex, &newLocation.x, &newLocation.y);
	if (!owner->move(newLocation)){
		onPathBlocked(newLocation);
	}
	else{
		++currentPathIndex;
	}
	return distance;
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
	//return fovMap->isInFov(location.x, location.y);
}

void CreatureAi::initAi(Creature &owner, Area &area){
	this->owner = &owner;
	this->area = &area;
	createPathMap();
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