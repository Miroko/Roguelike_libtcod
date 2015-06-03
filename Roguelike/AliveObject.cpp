#include "AliveObject.h"
#include "Engine.h"

#include "iostream"

void AliveObject::createFovMap(){
	fovMap = std::shared_ptr<TCODMap>(new TCODMap(Engine::area.bounds.getWidth(), Engine::area.bounds.getHeight()));

	int startX = 0;
	int startY = 0;
	int endX = fovMap->getWidth();
	int endY = fovMap->getHeight();
	
	for (int x = startX; x < endX; x++){
		for (int y = startY; y < endY; y++){		
			fovMap->setProperties(x, y,
				Engine::area.staticObjects[x][y]->isTransparent, Engine::area.staticObjects[x][y]->isPassableBy(*this));
		}
	}
}

void AliveObject::calculateFov(){
	fovMap->computeFov(location.x, location.y, 0, true, FOV_RESTRICTIVE);
}

bool AliveObject::inFov(int x, int y){
	return fovMap->isInFov(x, y);
}

float AliveObject::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	AliveObject thisObject = *static_cast<AliveObject*>(userData);
	if (Engine::area.staticObjects[xTo][yTo]->isPassableBy(thisObject) == false) return 0;

	for (auto &o : Engine::area.dynamicObjects){

		// Computing path to target
		if (o.get() == thisObject.target){
			return 1;
		}

		if (o->location.x == xTo && o->location.y == yTo){
			if (thisObject.isBlockedBy(*o)){
				return 0;
			}
		}
	}

	return 1;
}

void AliveObject::createPathMap(){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		Engine::area.bounds.getWidth(),
		Engine::area.bounds.getHeight(),
		new PathCostCallback(),
		this));
}

void AliveObject::calculatePath(int toX, int toY){
	pathMap->compute(location.x, location.y, toX, toY);
}

void AliveObject::moveOnPath(){
	int x;
	int y;
	if(pathMap->walk(&x, &y, true) == false){ 
		// Stuck
	}
	else{
		if (target->location.x == x && target->location.y == y){
			// Target in next spot
		}
		else{
			location.x = x;
			location.y = y;
			calculateFov();
		}		
	}
}

void AliveObject::setTarget(DynamicObject *target){
	this->target = target;
	calculatePath(target->location.x, target->location.y);
}

bool AliveObject::moveTowardsTarget(){
	//int desX, desY;
	//pathMap->getDestination(&desX, &desY);
	//if (target->location != Point2D(desX, desY)){
		// Target moved, recalculate path
		calculatePath(target->location.x, target->location.y);
	//}	
	int x, y;
	if (pathMap->walk(&x, &y, true) == true){
		if (target->location == Point2D(x, y)){
			// Target in next point
			return true;
		}
		else{
			// Move towards target
			location.x = x;
			location.y = y;
		}
	}
	else{
		// Stuck
	}
	return false;
}

void AliveObject::attack(DynamicObject &target){
	target.takeDamage(weapon->damage);
}

void AliveObject::update(){
	if (target != nullptr){
		if (moveTowardsTarget()){
			attack(*target);
		}
	}	
}