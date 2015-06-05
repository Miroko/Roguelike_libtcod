#pragma once
#include "StaticObject.h"
#include "AliveObject.h"
#include "Item.h"
#include "Rectangle.h"
#include "vector"
#include "memory"
#include "PathFinder.h"
class Area
{
private:
	bool requireClean = false;
public:
	Rectangle bounds;

	//Static objects
	std::vector<std::vector<std::shared_ptr<StaticObject>>> staticObjects;

	void setStaticObject(std::shared_ptr<StaticObject> staticObject, Point2D &location);

	//Dynamic objects
	std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;

	void killDynamicObject(DynamicObject &dynamicObject);
	void cleanDeadObjects();
	bool moveDynamicObject(DynamicObject *dynamicObject, Point2D &toLocation);
	bool placeDynamicObject(std::shared_ptr<DynamicObject> dynamicObject, Point2D &location);
	std::vector<DynamicObject*> getDynamicObjectsAt(Point2D &location);
	
	//Alive objects
	bool placeAliveObject(std::shared_ptr<AliveObject> aliveObject, Point2D &location);

	Area(int size, std::shared_ptr<StaticObject> &base);
	Area(){}
};

