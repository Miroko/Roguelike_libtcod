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
public:
	Rectangle bounds;

	std::vector<std::vector<std::shared_ptr<StaticObject>>> staticObjects;
	std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;

	void setStaticObject(std::shared_ptr<StaticObject> staticObject, Point2D &location);
	bool placeDynamicObject(std::shared_ptr<DynamicObject> dynamicObject, Point2D &location);
	bool placeAliveObject(std::shared_ptr<AliveObject> aliveObject, Point2D &location);

	bool moveDynamicObject(DynamicObject *dynamicObject, Point2D &toLocation);

	Area(int size, std::shared_ptr<StaticObject> &base);
	Area(){}
};

