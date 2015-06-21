#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "Armor.h"
#include "AliveObjectEffect.h"
#include "PointerContainer.h"
#include "Consumable.h"
#include <memory>

class AliveObject : public DynamicObject
{
	
public:
	//FOV
	static const int FOV_RADIUS_MAX = 0;
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
	std::shared_ptr<Weapon> weapon = nullptr;
	std::shared_ptr<Armor> armorHead = nullptr;
	std::shared_ptr<Armor> armorBody = nullptr;
	std::shared_ptr<Armor> armorHand = nullptr;
	std::shared_ptr<Armor> armorLeg = nullptr;
	void equip(std::shared_ptr<Item> equipment);

	//Effects
	PointerContainer<AliveObjectEffect> effects;
	void addEffect(std::shared_ptr<AliveObjectEffect> effect);
	void consume(std::shared_ptr<Item> consumable);
	
	//Combat
	static const int RANGED_SHOOT_DISTANCE_MAX = 4;
	std::shared_ptr<DynamicObject> target = nullptr;
	void setTarget(std::shared_ptr<DynamicObject> target);
	void damage(std::shared_ptr<DynamicObject> &target);
	void attackMelee(std::shared_ptr<DynamicObject> &target);
	void attackRanged(std::shared_ptr<DynamicObject> &target);
	bool moveOnPath();
	bool targetInFov();
	void calculatePathToTarget();

	void onTakeDamage(int amount);

	void update();

	AliveObject(Glyph glyph, std::string name, Size size, int health, const LootContainer &loot) :
		DynamicObject(glyph, name, size, true, health, loot){};
};