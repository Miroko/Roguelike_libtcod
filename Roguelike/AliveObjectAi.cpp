#include "AliveObjectAi.h"
#include "AliveObject.h"
#include "Area.h"
#include "Engine.h"
#include "Random.h"

Rectangle AliveObjectAi::SCAN_AREA = Rectangle();

Rectangle& AliveObjectAi::getScanArea(Point2D &location, int distance){
	SCAN_AREA.start = location;
	SCAN_AREA.end = location;
	SCAN_AREA.expand(distance);
	return SCAN_AREA;
}

void AliveObjectAi::createFovMap(Area &area){
	fovMap = std::shared_ptr<TCODMap>(new TCODMap(area.bounds.getWidth(), area.bounds.getHeight()));
	int startX = 0;
	int startY = 0;
	int endX = fovMap->getWidth();
	int endY = fovMap->getHeight();
	for (int x = startX; x < endX; x++){
		for (int y = startY; y < endY; y++){
			fovMap->setProperties(x, y,
				area.staticObjects[x][y]->transparent, area.staticObjects[x][y]->passable());
		}
	}
}

void AliveObjectAi::calculateFov(Area &area, AliveObject &owner){
	//Update fov map
	for (auto &o : area.dynamicObjects){
		if (o->isDead) fovMap->setProperties(o->location.x, o->location.y,
			area.staticObjects[o->location.x][o->location.y]->transparent,
			area.staticObjects[o->location.x][o->location.y]->passable());
		else{
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable());
		}
	}
	//Compute
	fovMap->computeFov(owner.location.x, owner.location.y, FOV_RADIUS_MAX, true, FOV_RESTRICTIVE);
}

bool AliveObjectAi::inFov(int x, int y){
	return fovMap->isInFov(x, y);
}

std::vector<std::shared_ptr<Door>> AliveObjectAi::getDoorsInFov(int maxDistance, AliveObject &owner){
	std::vector<std::shared_ptr<Door>> doorsInFov;
	Rectangle scanArea = Rectangle(owner.location, owner.location);
	scanArea.expand(maxDistance);
	for (auto &dynamicObject : Engine::area.getDynamicObjects(scanArea)){
		if (inFov(dynamicObject->location.x, dynamicObject->location.y)){
			std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(dynamicObject);
			if (door != nullptr){
				doorsInFov.push_back(door);
			}
		}
	}
	return doorsInFov;
}

float AliveObjectAi::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	AliveObject *thisObject = static_cast<AliveObject*>(userData);
	if (Engine::area.staticObjects[xTo][yTo]->passable() == false) return 0;

	for (auto &o : Engine::area.dynamicObjects){
		if (o->isDead) continue;

		if (o->location.x == xTo && o->location.y == yTo){
			if (!o->passable()){
				if (o->location == thisObject->ai.targetLocation){
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

void AliveObjectAi::createPathMap(Area &area, AliveObject &owner){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		area.bounds.getWidth(),
		area.bounds.getHeight(),
		new PathCostCallback(),
		&owner));
}

void AliveObjectAi::calculatePath(Point2D &location, AliveObject &owner){
	pathMap->compute(owner.location.x, owner.location.y, location.x, location.y);
}

void AliveObjectAi::setTargetLocation(Point2D &location){
	targetLocation = location;
}

void AliveObjectAi::setCombatTarget(DynamicObject &target){
	this->combatTarget = &target;
}

//Returns true if destination in next spot
bool AliveObjectAi::moveOnPath(AliveObject &owner){
	if (!pathMap->isEmpty()){
		int nextX, nextY;
		if (pathMap->walk(&nextX, &nextY, false) == true){
			int destinationX, destinationY;
			pathMap->getDestination(&destinationX, &destinationY);
			if (nextX == destinationX &&
				nextY == destinationY){
				return true;
			}
			else{
				// Move
				owner.location.x = nextX;
				owner.location.y = nextY;
			}
		}
		else{
			// Stuck
		}
	}
	else{
		//Path finished
	}
	return false;
}

bool AliveObjectAi::targetInFov(){
	if (inFov(combatTarget->location.x, combatTarget->location.y)) return true;
	else return false;
}

void AliveObjectAi::startCombat(DynamicObject &target){
	if (state != NONE){
		setCombatTarget(target);
		state = AliveObjectAi::COMBAT;
	}
}

bool AliveObjectAi::closeDoor(AliveObject &owner){
	std::shared_ptr<Door> doorToClose = nullptr;
	for (auto &dynamicObject : Engine::area.getDynamicObjects(getScanArea(owner.location, DISTANCE_MEDIUM))){
		if (doorToClose != nullptr){
			if (dynamicObject->location == doorToClose->location) return false;
		}
		std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(dynamicObject);
		if (door != nullptr && doorToClose == nullptr){
			if (door->isOn){ //Is open
				doorToClose = door;
			}
		}
	}
	if (doorToClose != nullptr){
		setTargetLocation(doorToClose->location);
		calculatePath(targetLocation, owner);
		if (moveOnPath(owner)){
			doorToClose->off(); //Close
		}
		return true;
	}
	return false;
}

bool AliveObjectAi::wander(AliveObject &owner){
	Point2D direction = Random::direction();
	Engine::area.moveDynamicObject(owner, owner.location + direction);
	return false;
}

bool AliveObjectAi::combat(AliveObject &owner){
	if (combatTarget != nullptr){
		if (!combatTarget->isDead){
			if (targetInFov()){ 
				//Target in fov, calculate new path to it
				targetLocation = combatTarget->location;
				calculatePath(targetLocation, owner);

				if (owner.weapon != nullptr){
					if (owner.weapon->type == Weapon::WEAPON_MELEE){
						if (moveOnPath(owner)) owner.attackMelee(*combatTarget);
						return true;
					}
					else if (owner.weapon->type == Weapon::WEAPON_RANGED){
						int distance = owner.location.distance(combatTarget->location);
						if (distance <= RANGED_SHOOT_DISTANCE_MAX){
							owner.attackRanged(*combatTarget);
						}
						else moveOnPath(owner);
						return true;
					}
				}
			}
			else{
				//Use old path
				if (moveOnPath(owner)){
					//Lost track
					return false;
				}
				else return true;
			}
		}
	}
	return false;
}

void AliveObjectAi::update(AliveObject &owner){
	calculateFov(Engine::area, owner);

	if (state != NONE){
		if (state == FREE){
			AiState nextState = FREE;
			Rectangle small = getScanArea(owner.location, DISTANCE_SMALL);
			Rectangle medium = getScanArea(owner.location, DISTANCE_MEDIUM);
			for (auto &dynamicObject : Engine::area.dynamicObjects){
				if (medium.contains(dynamicObject->location)){
					std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(dynamicObject);
					if (door != nullptr){
						if (door->isOn){
							nextState = CLOSE_DOOR; break;
						}
					}
					if (small.contains(dynamicObject->location)){
						std::shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(dynamicObject);
						if (creature != nullptr){
							if (creature.get() != &owner){
								nextState = IDLE; break;
							}
						}
					}
				}
			}
			if (nextState == FREE){
				nextState = WANDER;
			}
			state = nextState;
		}
		else if (state == IDLE){
			if (Random::generator.get(0.0, 1.0) < 0.05){
				state = WANDER;
			}
		}
		else if (state == WANDER){
			aiActions.push_back([&](AliveObject& owner) { return wander(owner); });
		}
		else if (state == CLOSE_DOOR){
			aiActions.push_back([&](AliveObject& owner) { return closeDoor(owner); });
		}
		else if (state == COMBAT){
			aiActions.push_back([&](AliveObject& owner) { return combat(owner); });
		}

		if (!aiActions.empty()){
			if (!aiActions.front()(owner)) state = FREE;
			aiActions.pop_front();
		}
	}

}