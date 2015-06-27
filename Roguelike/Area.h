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

	std::vector<std::vector<StaticObject*>> staticObjects;
	void setStaticObject(StaticObject &staticObject, Point2D &location);

	std::vector<std::shared_ptr<Portal>> portals;
	void placePortal(std::shared_ptr<Portal> portal, Point2D &location);

	std::vector<std::shared_ptr<Creature>> creatures;
	void placeCreature(std::shared_ptr<Creature> creature, Point2D &location);
	bool moveCreature(Creature &creature, Point2D &location);
	std::vector<std::shared_ptr<Creature>*> getCreatures(Point2D &location);
	std::vector<std::shared_ptr<Creature>*> getCreatures(Rectangle &bounds);

	std::vector<std::shared_ptr<OperatableObject>> operatableObjects;
	void placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location);
	bool moveOperatable(std::shared_ptr<OperatableObject> &operatable, Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>*> getOperatables(Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>*> getOperatables(Rectangle &bounds);
	
	std::vector<std::shared_ptr<Item>> items;
	void placeItem(std::shared_ptr<Item> item, Point2D &toLocation);
	std::vector<std::shared_ptr<Item>*> getItemsAt(Point2D &location);
	void removeItem(std::shared_ptr<Item> &item);

	void killDynamicObject(DynamicObject &dynamicObject);
	void cleanDeadDynamicObjects();

	void update();



	Area(int size, StaticObject &base);
	Area(){}
};

