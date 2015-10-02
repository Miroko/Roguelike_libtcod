#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "AiFov.h"
#include <memory>
#include <vector>

class Area;
class Creature;
class Weapon;
class WeaponAction;
class DynamicObject;
class OperatableObject;
class CreatureAi
{
public:
	class PathCostCallback : public ITCODPathCallback{
		public: float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const;
	};

	Creature *owner;

	Area *area;
	std::shared_ptr<TCODPath> pathMap;
	AiFov fov;

	int currentPathIndex;

	void calculateFov();
	bool inFov(Point2D &location);

	void createPathMap();
	void calculatePath(Point2D &location);
	virtual void onTakeDamage(DynamicObject &attacker);
	virtual void onCreatureInFov(Creature &creature, int distance);
	virtual void onOperatableInFov(OperatableObject &operatable, int distance);
	virtual void nextToDestination(Point2D &location);
	virtual void onPathBlocked(Point2D &location);
	virtual void onPathEnd(Point2D &location);
	//Returns path distance to destination
	int moveOnPath();

	virtual void initAi(Creature &owner, Area &area);
	virtual void update();
	
	virtual std::shared_ptr<CreatureAi> copy() = 0;

	CreatureAi() :
		fov(AiFov(20, 5)){};
};

