#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "memory"

class AliveObject : public DynamicObject
{
	
public:
	//FOV
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
	void moveOnPath();

	//Stats
	int health = 100;
	void takeDamage(int amount);

	//Equipment
	Weapon *weapon;

	//Attack
	AliveObject *target = nullptr;
	void setTarget(AliveObject *target);
	bool moveTowardsTarget();
	void attack();

	void DynamicObject::update();

	AliveObject(Glyph glyph, std::string name, Size size, Loot *loot) :
		DynamicObject(glyph, name, size, loot){};
};