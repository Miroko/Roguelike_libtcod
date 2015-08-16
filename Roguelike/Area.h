#pragma once
#include "OperatableObject.h"
#include "Creature.h"
#include "Item.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Tile.h"
#include "PlayerController.h"
#include <vector>
#include <memory>

class Area
{
private:
	Rectangle bounds;
	bool cleaningRequired = false;

public:
	static bool SEE_THROUGH;

	std::vector<std::vector<Tile*>> tiles;
	void placeTile(Tile &tile, Point2D &location);
	void placeTile(Tile &tile, Point2D &location, Tile &placeOnNearest);
	Tile *getTile(Point2D &location);
	Point2D getNearestTile(Point2D &location, Tile &tile);
	Point2D getNearestTile(Point2D &location, Tile::Type type);

	std::vector<std::shared_ptr<Creature>> creatures;
	void placeCreature(std::shared_ptr<Creature> creature, Point2D &location);
	std::vector<std::shared_ptr<Creature>*> getCreatures(Point2D &location);
	std::vector<std::shared_ptr<Creature>*> getCreatures(Rectangle &bounds);

	std::vector<std::shared_ptr<OperatableObject>> operatableObjects;
	void placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>*> getOperatables(Point2D &location);
	std::vector<std::shared_ptr<OperatableObject>*> getOperatables(Rectangle &bounds);
	
	std::vector<std::shared_ptr<Item>> items;
	void placeItem(std::shared_ptr<Item> item, Point2D &toLocation);
	std::vector<std::shared_ptr<Item>*> getItemsAt(Point2D &location);
	void removeItem(std::shared_ptr<Item> &item);

	Rectangle &getBounds();

	bool passable(Point2D &location, DynamicObject &dynamicObjectMoving);

	void requireClean();	
	void cleanDeadDynamicObjects();

	//generate area
	virtual void generate() = 0;
	//rezise area and fill with tile
	void generateBase(Rectangle bounds, Tile &tile);
	void generateEdge(Tile &tile, int size, int randomTilesPerEdgeTile);

	void initAi();

	void update();
	void render();

	Area(){}
};

