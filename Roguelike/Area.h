#pragma once
#include "OperatableObject.h"
#include "Creature.h"
#include "Item.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Tile.h"
#include "AreaContainer.h"
#include <vector>
#include <memory>
#include <forward_list>

class Area
{
private:
	Rectangle bounds;
	int itemRenderRateCounter = 0;
	static const int itemRenderNumberMax = 10;
	int itemRenderNumberCurrent = 0;
	std::vector<std::shared_ptr<DynamicObject>> dynamicObjectsDead;

public:
	std::vector<std::vector<AreaContainer>> areaContainers;
	std::forward_list<std::shared_ptr<DynamicObject>> dynamicObjectsAlive;

	Rectangle& getBounds(){ return bounds; }
	int getItemRenderNumberCurrent(){ return itemRenderNumberCurrent; };

	//placement
	void placeTile(Tile &tile, Point2D &location);
	void placeTile(Tile &tile, Point2D &location, Tile &placeOnNearest);
	Tile* getTile(Point2D &location);
	Point2D getNearestTile(Point2D &location, Tile &tile);
	Point2D getNearestTile(Point2D &location, Tile::Type type);

	void placeCreature(std::shared_ptr<Creature> creature, Point2D &location);
	Creature& getCreature(Point2D &location);
	std::vector<Creature*> getCreatures(Rectangle &bounds);

	void placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location);
	OperatableObject& getOperatable(Point2D &location);
	std::vector<OperatableObject*> getOperatables(Rectangle &bounds);
	
	void placeItem(std::shared_ptr<Item> item, Point2D &location);
	std::vector<std::shared_ptr<Item>>& getItems(Point2D &location);
	void removeItem(std::shared_ptr<Item> &item);
	//------

	//movement
	bool isPassable(Point2D &location, DynamicObject &dynamicObjectMoving);
	bool moveDynamicObject(DynamicObject &dynamicObject, Point2D &location);
	//------

	//destruction
	void destroyDynamicObject(DynamicObject &dynamicObject);
	void cleanDeadObjects();
	//------

	void initAi();

	void update();
	void render();

	//resize area and fill with tile
	void generateBase(Rectangle bounds, Tile &tile);
	void generateEdge(Tile &tile, int size, int randomTilesPerEdgeTile);

	virtual void generate() = 0;

	Area(){}
};

