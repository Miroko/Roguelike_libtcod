#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "OperatableObject.h"
#include <memory>

class Area;
class Creature;
class CreatureAi
{
public:
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap();
	void calculateFov();

	bool cheapPathCalculation;
	int currentPathIndex;
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{ public: float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const; };
	void createPathMap();
	void calculatePath(Point2D &location, bool cheap = true);
	Point2D targetLocation;

	virtual void onTakeDamage(DynamicObject &attacker);
	virtual void onCreatureInFov(Creature &creature, int distance);
	virtual void onOperatableInFov(OperatableObject &operatable, int distance);
	virtual void nextToDestination(Point2D &location);
	virtual void onPathBlocked(Point2D &location);
	virtual void onPathEnd(Point2D &location);

	Creature *owner;
	Area *area;
	//Returns true if destination in next spot
	bool moveOnPath();
	bool inFov(Point2D &location);
	virtual void initAi(Creature &owner, Area &area);
	virtual void update();
	
	virtual std::shared_ptr<CreatureAi> copy() = 0;

	CreatureAi(){};
};

