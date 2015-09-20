#include "CreatureAi.h"
#include "Area.h"
#include "Weapon.h"
#include "Engine.h"

void CreatureAi::createFovMap(){
	Rectangle fovBounds = area->getBounds();
	fovMap = std::shared_ptr<TCODMap>(new TCODMap(fovBounds.getWidth(), fovBounds.getHeight()));
	for (int x = fovBounds.start.x; x < fovBounds.end.x; x++){
		for (int y = fovBounds.start.y; y < fovBounds.end.y; y++){
			fovMap->setProperties(x, y,
				area->tiles[x][y]->transparent, false); // walkability from callback function
		}
	}
}
float CreatureAi::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	CreatureAi *thisObject = static_cast<CreatureAi*>(userData);
	float walkCost = 0; // 0 == unwalkable
	walkCost = (float)thisObject->area->tiles[xTo][yTo]->walkCost;
	if (walkCost != 0 && !thisObject->cheapPathCalculation){
		Point2D destination;
		thisObject->pathMap->getDestination(&destination.x, &destination.y);
		if (xTo == destination.x &&	yTo == destination.y) return walkCost;
		else{
			for (auto &creature : thisObject->area->creatures){
				if (creature->isDead) continue;
				if (creature->location.x == xTo && creature->location.y == yTo){
					if (!creature->passable(*thisObject->owner)) return 0;
				}
			}
			for (auto &operatable : thisObject->area->operatableObjects){
				if (operatable->isDead) continue;
				if (operatable->location.x == xTo && operatable->location.y == yTo){
					if (!operatable->passable(*thisObject->owner)) return 0;
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
	for (auto &o : area->creatures){
		if (!o->isDead){
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable(*owner));
		}
		else{
			//if dead use static object
			fovMap->setProperties(o->location.x, o->location.y,
				area->tiles[o->location.x][o->location.y]->transparent, false);
		}
	}
	for (auto &o : area->operatableObjects){
		if (!o->isDead){
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable(*owner));
		}
		else{
			fovMap->setProperties(o->location.x, o->location.y,
				area->tiles[o->location.x][o->location.y]->transparent, false);
		}
	}
	fovMap->computeFov(owner->location.x, owner->location.y, 0, true, FOV_RESTRICTIVE);
}
void CreatureAi::calculatePath(Point2D &location, bool cheapPathing){
	cheapPathCalculation = cheapPathing;
	pathMap->compute(owner->location.x, owner->location.y, location.x, location.y);
	currentPathIndex = 0;
	cheapPathCalculation = true;
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
	return fovMap->isInFov(location.x, location.y);
}
void CreatureAi::initAi(Creature &owner, Area &area){
	this->owner = &owner;
	this->area = &area;
	createFovMap();
	createPathMap();
	calculateFov();
}
void CreatureAi::update(){
	calculateFov();
	for (auto &creature : area->creatures){
		if (inFov(creature->location)){
			if (creature.get() != owner){
				onCreatureInFov(*creature, creature->location.distance(owner->location));
			}
		}
	}
	for (auto &operatable : area->operatableObjects){
		if (inFov(operatable->location)){
			onOperatableInFov(*operatable, operatable->location.distance(owner->location));
		}
	}
}