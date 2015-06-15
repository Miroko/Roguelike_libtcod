#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "AliveObjectEffect.h"
#include "PointerContainer.h"
#include "Consumable.h"
#include <memory>

class AliveObject : public DynamicObject
{
	
public:
	//FOV
	const int FOV_RADIUS_MAX = 0;
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap();
	void calculateFov();
	bool inFov(int x, int y);

	//Pathfinder
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{
	public:
		float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const;
	};
	void createPathMap();
	void calculatePath(int toX, int toY);
	
	//Equipment
	Weapon *weapon = nullptr;
	void equip(Item *equipment);

	//Effects
	PointerContainer<AliveObjectEffect> effects;
	void addEffect(std::shared_ptr<AliveObjectEffect> effect);
	void consume(std::shared_ptr<Item> consumable);

	//Attack
	DynamicObject *target = nullptr;
	void setTarget(DynamicObject *target);
	bool moveTowardsTarget();
	void damage(DynamicObject &target);

	void update();

	AliveObject(Glyph glyph, std::string name, Size size, int health, const Loot &loot) :
		DynamicObject(glyph, name, size, true, health, loot){};
};