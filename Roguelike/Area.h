#pragma once
#include "StaticObject.h"
#include "AliveObject.h"
#include "Item.h"
#include "Portal.h"
#include "Rectangle.h"
#include <vector>
#include <memory>
class Area
{
private:
	bool requireClean = false;
public:
	Rectangle bounds;

	//Static objects
	std::vector<std::vector<std::shared_ptr<StaticObject>>> staticObjects;

	void setStaticObject(std::shared_ptr<StaticObject> staticObject, Point2D &location);

	//Portals
	std::vector<std::shared_ptr<Portal>> portals;
	void placePortal(std::shared_ptr<Portal> &portal, Point2D &location);

	//Dynamic objects
	std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;

	void killDynamicObject(DynamicObject &dynamicObject);
	void cleanDeadObjects();
	bool moveDynamicObject(DynamicObject &dynamicObject, Point2D &toLocation);
	bool placeDynamicObject(std::shared_ptr<DynamicObject> dynamicObject, Point2D &location);
	std::vector<std::shared_ptr<DynamicObject>> getDynamicObjectsAt(Point2D &location);

	//Inits fov and pathfinding
	bool placeAliveObject(std::shared_ptr<AliveObject> aliveObject, Point2D &location);

	//Items
	std::vector<std::shared_ptr<Item>> items;
	void placeItem(std::shared_ptr<Item> &item, Point2D &toLocation);
	void removeItem(Item &item);
	std::vector<std::shared_ptr<Item>> getItemsAt(Point2D &location);

	Area(int size, const std::shared_ptr<StaticObject> &base);
	Area(){}
};

