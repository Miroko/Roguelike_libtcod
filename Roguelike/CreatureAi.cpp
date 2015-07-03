#include "CreatureAi.h"
#include "Engine.h"

void CreatureAi::createFovMap(){
	//todo: smaller fov map
	Rectangle fovBounds = engine::areaHandler.getCurrentArea()->getBounds();
	fovMap = std::shared_ptr<TCODMap>(new TCODMap(fovBounds.getWidth(), fovBounds.getHeight()));
	for (int x = fovBounds.start.x; x < fovBounds.end.x; x++){
		for (int y = fovBounds.start.y; y < fovBounds.end.y; y++){
			fovMap->setProperties(x, y,
				engine::areaHandler.getCurrentArea()->tiles[x][y]->type == GameObject::FLOOR,
				engine::areaHandler.getCurrentArea()->tiles[x][y]->type == GameObject::WALL);
		}
	}
}
float CreatureAi::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	float walkability = 0; // 0 == unwalkable

	CreatureAi *thisObject = static_cast<CreatureAi*>(userData);
	if (!engine::areaHandler.getCurrentArea()->tiles[xTo][yTo]->type == GameObject::WALL) walkability = 1;
	else return 0;

	for (auto &o : engine::areaHandler.getCurrentArea()->creatures){
		if (o->isDead) continue;
		if (o->location.x == xTo && o->location.y == yTo){
			if (!o->passable(*thisObject->owner)){
				if (o->location == thisObject->targetLocation){
					walkability = 1;
				}
				else{
					return 0;
				}
			}
		}
	}
	for (auto &o : engine::areaHandler.getCurrentArea()->operatableObjects){
		if (o->isDead) continue;
		if (o->location.x == xTo && o->location.y == yTo){
			if (!o->passable(*thisObject->owner)){
				if (o->location == thisObject->targetLocation){
					walkability = 1;
				}
				else{
					return 0;
				}
			}
		}
	}
	return walkability;
}
void CreatureAi::createPathMap(){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		engine::areaHandler.getCurrentArea()->getBounds().getWidth(),
		engine::areaHandler.getCurrentArea()->getBounds().getHeight(),
		new PathCostCallback(),
		this));
}
void CreatureAi::calculateFov(){
	for (auto &o : engine::areaHandler.getCurrentArea()->creatures){
		if (!o->isDead){
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable(*owner));
		}
		else{
			//if dead use static object
			fovMap->setProperties(o->location.x, o->location.y,
				engine::areaHandler.getCurrentArea()->tiles[o->location.x][o->location.y]->type == GameObject::FLOOR,
				engine::areaHandler.getCurrentArea()->tiles[o->location.x][o->location.y]->type == GameObject::WALL);
		}
	}
	for (auto &o : engine::areaHandler.getCurrentArea()->operatableObjects){
		if (!o->isDead){
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable(*owner));
		}
		else{
			fovMap->setProperties(o->location.x, o->location.y,
				engine::areaHandler.getCurrentArea()->tiles[o->location.x][o->location.y]->type == GameObject::FLOOR,
				engine::areaHandler.getCurrentArea()->tiles[o->location.x][o->location.y]->type == GameObject::WALL);
		}
	}
	fovMap->computeFov(owner->location.x, owner->location.y, 0, true, FOV_RESTRICTIVE);
}
void CreatureAi::calculatePath(Point2D &location){
	pathMap->compute(owner->location.x, owner->location.y, location.x, location.y);
}
bool CreatureAi::moveOnPath(){
	Point2D nextLocation;
	if (!pathMap->isEmpty()){
		if (pathMap->walk(&nextLocation.x, &nextLocation.y, false) == true){
			Point2D destination;
			pathMap->getDestination(&destination.x, &destination.y);
			if (nextLocation == destination){
				onDestination(nextLocation);
				return true;
			}
			else{
				owner->location = nextLocation;
			}
		}
		else{
			onPathBlocked(nextLocation);
		}
	}
	else{
		onPathEnd(nextLocation);
	}
	return false;
}
void CreatureAi::onTakeDamage(DynamicObject &attacker){
	
}
void CreatureAi::onCreatureInFov(Creature &creature, int distance){

}
void CreatureAi::onOperatableInFov(OperatableObject &operatable, int distance){

}
void CreatureAi::onDestination(Point2D &location){

}
void CreatureAi::onPathBlocked(Point2D &location){

}
void CreatureAi::onPathEnd(Point2D &location){

}
void CreatureAi::setTargetLocation(Point2D &location){
	targetLocation = location;
	calculatePath(targetLocation);
}
bool CreatureAi::inFov(Point2D &location){
	return fovMap->isInFov(location.x, location.y);
}
void CreatureAi::initAi(Creature &owner){
	this->owner = &owner;
	createFovMap();
	createPathMap();
	calculateFov();
}
void CreatureAi::update(){
	calculateFov();
	for (auto &creature : engine::areaHandler.getCurrentArea()->creatures){
		if (inFov(creature->location)){
			onCreatureInFov(*creature, creature->location.distance(owner->location));
		}
	}
	for (auto &operatable : engine::areaHandler.getCurrentArea()->operatableObjects){
		if (inFov(operatable->location)){
			onOperatableInFov(*operatable, operatable->location.distance(owner->location));
		}
	}
	moveOnPath();
}