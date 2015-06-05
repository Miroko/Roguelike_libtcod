#include "Area.h"
#include <iostream>
#include <algorithm>

Area::Area(int size, std::shared_ptr<StaticObject> &base) :
bounds(Rectangle(Point2D(0, 0), Point2D(size, size)))
{
	staticObjects.resize(bounds.getWidth());
	for (int x = 0; x < bounds.getWidth(); x++){
		staticObjects[x].resize(bounds.getHeight(), base);
	}	
}

void Area::setStaticObject(std::shared_ptr<StaticObject> staticObject, Point2D &location){
	staticObjects[(int)location.x][(int)location.y] = staticObject;
}

//Returns true when object placed. First tries to place at set location then by expanding placement area
//Should always return true else in infinite loop trying to find free spot
bool Area::placeDynamicObject(std::shared_ptr<DynamicObject> dynamicObject, Point2D &location){
	if (moveDynamicObject(dynamicObject.get(), location)){
		dynamicObjects.push_back(dynamicObject);
		return true;
	}
	else {
		//Increase placement area until placed on open spot
		Point2D alternativeLocation = location;
		int offset = 1;
		while (true){ //Every object must be placed somewhere
			for (alternativeLocation.x = location.x - offset; alternativeLocation.x < location.x + offset; alternativeLocation.x++){
				for (alternativeLocation.y = location.y - offset; alternativeLocation.y < location.y + offset; alternativeLocation.y++){
					if (moveDynamicObject(dynamicObject.get(), alternativeLocation)){
						dynamicObjects.push_back(dynamicObject);
						return true;
					}
					else{
						std::cout << alternativeLocation.x << "," << alternativeLocation.y << "\n";
					}
				}
			}
			++offset;
		}
	}
	return false;
}

bool Area::placeAliveObject(std::shared_ptr<AliveObject> aliveObject, Point2D &location){
	if (placeDynamicObject(aliveObject, location)){
		aliveObject->createFovMap();
		aliveObject->calculateFov();
		aliveObject->createPathMap();
		return true;
	}
	else return false;
}

bool Area::moveDynamicObject(DynamicObject *dynamicObject, Point2D &toLocation){
	if (bounds.contains(toLocation)){
		if (staticObjects[(int)toLocation.x][(int)toLocation.y]->isPassableBy(*dynamicObject) == false) {
			return false;
		}
		for (auto &o : dynamicObjects){
			if (o->location.x == toLocation.x && o->location.y == toLocation.y){
				if (dynamicObject->isBlockedBy(*o)){
					return false;
				}
			}
		}
		// Can move
		dynamicObject->location = toLocation;
		return true;
	}
	return false;
}

std::vector<DynamicObject*> Area::getDynamicObjectsAt(Point2D &location){
	std::vector<DynamicObject*> objectsAtLocation;
	for (auto &dynamicObject : dynamicObjects){
		if (dynamicObject->location == location){
			objectsAtLocation.push_back(dynamicObject.get());
		}
	}
	return objectsAtLocation;
}

void Area::killDynamicObject(DynamicObject &dynamicObject){
	for (auto &o : dynamicObjects){
		if (o.get() == &dynamicObject){
			o->isDead = true;
			requireClean = true;
		}
	}
}

void Area::cleanDeadObjects(){
	if (requireClean){
		auto &o = dynamicObjects.begin();
		while (o != dynamicObjects.end()){
			if (o->get()->isDead){
				o = dynamicObjects.erase(o);
			}
			else ++o;
		}
		requireClean = false;
	}
}