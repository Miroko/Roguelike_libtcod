#pragma once
#include "StaticObject.h"
#include "AliveObject.h"
#include "Creature.h"
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

	std::vector<std::vector<std::shared_ptr<StaticObject>>> staticObjects;
	void setStaticObject(std::shared_ptr<StaticObject> staticObject, Point2D &location);

	std::vector<std::shared_ptr<Portal>> portals;
	void placePortal(std::shared_ptr<Portal> &portal, Point2D &location);

	std::vector<std::shared_ptr<Creature>> creatures;
	void placeCreature(std::shared_ptr<Creature> creature, Point2D &location);
	bool moveCreature(Creature &creature, Point2D &location);
	std::vector<std::shared_ptr<Creature>> getCreatures(Point2D &location);
	std::vector<std::shared_ptr<Creature>> getCreatures(Rectangle &bounds);

	std::vector<std::shared_ptr<OperatableObject>> operatableObjects;
	void placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location);
	bool moveOperatable(OperatableObject &operatable, Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>> getOperatables(Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>> getOperatables(Rectangle &bounds);
	
	std::vector<std::shared_ptr<Item>> items;
	void placeItem(std::shared_ptr<Item> &item, Point2D &toLocation);
	std::vector<std::shared_ptr<Item>> getItemsAt(Point2D &location);
	void removeItem(Item &item);

	void killDynamicObject(DynamicObject &dynamicObject);
	void cleanDeadDynamicObjects();

	void update();

	//bool moveDynamicObject(DynamicObject &dynamicObject, Point2D &toLocation);
	//bool placeDynamicObject(std::shared_ptr<DynamicObject> dynamicObject, Point2D &location);
	//std::vector<std::shared_ptr<DynamicObject>> getDynamicObjects(Point2D &location);
	//std::vector<std::shared_ptr<DynamicObject>> getDynamicObjects(Rectangle &bounds);

	//Dynamic objects including Alive objects
	//std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;
	//Alive objects
	//std::vector<std::shared_ptr<DynamicObject>> alivecObjects;

	//Init fov and pathfinding
	//Store to dynamic and alive objects
	//bool placeAliveObject(std::shared_ptr<AliveObject> aliveObject, Point2D &location);



	Area(int size, const std::shared_ptr<StaticObject> &base);
	Area(){}
};

