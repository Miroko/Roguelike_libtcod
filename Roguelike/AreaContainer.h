#pragma once
#include <vector>
#include <memory>

class Tile;
class Item;
class OperatableObject;
class Creature;
class DynamicObject;
class AreaContainer
{
public:
	Tile *tile;
	OperatableObject *operatableObject = nullptr;
	Creature *creature = nullptr;
	std::vector<std::shared_ptr<Item>> items;

	bool isPassable(DynamicObject &dynamicObjectMoving);
	double getTransparency();

	Item& getItemToRender(int itemRenderNumberCurrent);

	AreaContainer(Tile &tile) :
		tile(&tile){}
};

