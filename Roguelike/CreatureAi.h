#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "OperatableObject.h"
#include <memory>

class Creature;
class CreatureAi
{
protected:
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap();
	void calculateFov();
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{ public: float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const; };
	void createPathMap();
	void calculatePath(Point2D &location);
	//Returns true if destination in next spot
	bool moveOnPath();
	Point2D targetLocation;

public:
	virtual void onTakeDamage(DynamicObject &attacker);
	virtual void onCreatureInFov(Creature &creature, int distance);
	virtual void onOperatableInFov(OperatableObject &operatable, int distance);
	virtual void onDestination(Point2D &location);
	virtual void onPathBlocked(Point2D &location);
	virtual void onPathEnd(Point2D &location);

	Creature *owner;
	bool inFov(Point2D &location);
	void setTargetLocation(Point2D &location);
	void initAi(Creature &owner);
	void update();
	
	CreatureAi(){};
};

