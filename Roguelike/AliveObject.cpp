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
		if (o == nullptr) continue;

		if (o->location.x == xTo && o->location.y == yTo){
			if (thisObject.isBlockedBy(*o)){				
				if (o.get() == thisObject.target){
					// Computing path to target
					return 1;
				}
				else{
					return 0;
				}
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

void AliveObject::setTarget(DynamicObject *target){
	this->target = target;
}

//Returns true if target in next spot else false
bool AliveObject::moveTowardsTarget(){
	if (inFov(target->location.x, target->location.y)){
		//If target can be seen be seen calculate new path to target
		calculatePath(target->location.x, target->location.y);
	}
	else{
		//Can't see target. Move towards using old path
	}
		
	if(!pathMap->isEmpty()){
		int x, y;
		if (pathMap->walk(&x, &y, false) == true){
			if (target->location == Point2D(x, y)){
				// Target is in next point
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
	}
	else{
		//Lost track
	}
	return false;
}

void AliveObject::attack(DynamicObject &target){
	target.onTakeDamage(weapon->damage);
}

void AliveObject::update(){
	calculateFov();
	if (target != nullptr){
		if (moveTowardsTarget()){
			attack(*target);
		}
	}	
}