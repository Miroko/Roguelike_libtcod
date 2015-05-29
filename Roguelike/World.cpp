#include "World.h"
#include "iostream"

World::World(){
	area = WorldArea(50);

	playerObject = std::shared_ptr<DynamicObject>(new Human("Player", Point2D(0, 0)));
	area.dynamicObjects.push_back(playerObject);
	
	placePlayer(*playerObject);
}

bool World::moveDynamicObject(DynamicObject &dynamicObject, Point2D &toLocation){
	if (area.bounds.contains(toLocation)){
		if (area.staticObjects[toLocation.x][toLocation.y]->isPassableBy(dynamicObject) == false) {
			return false;
		}
		for (auto &o : area.dynamicObjects){
			if (o->location.x == toLocation.x && o->location.y == toLocation.y){
				if (dynamicObject.isBlockedBy(*o)){
					return false;
				}
			}
		}
		// Can move
		dynamicObject.location = toLocation;
		return true;
	}
	return false;
}

void World::placePlayer(DynamicObject &playerObject){
	moveDynamicObject(playerObject, area.bounds.getCenterPoint());
}

void World::update(float elapsed){
	for (auto &dynamicObject : area.dynamicObjects){
		dynamicObject->update(elapsed);
	}
}