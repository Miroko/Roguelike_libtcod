/*
#pragma once
#include "libtcod.hpp"
#include "Door.h"
#include "Rectangle.h"
#include <memory>
#include <deque>
#include <functional>

class Area;
class AliveObject;
class CreatureAi
{
private:

	static Rectangle SCAN_Area;
	static Rectangle& getScanArea(Point2D &location, int distance);
public:
	enum AiState{
		NONE, //No ai, player etc.
		FREE,
		IDLE,
		WANDER,
		CLOSE_DOOR,
		COMBAT
	};
	AiState state = NONE;
	std::deque<std::function<bool(AliveObject&)>> aiActions;
	
	//FOV
	static const int FOV_RADIUS_MAX = 0;
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap(Area &Area);
	void calculateFov(Area &Area, AliveObject &owner);
	bool inFov(int x, int y);
	std::vector<std::shared_ptr<Door>> getDoorsInFov(int maxDistance, AliveObject &owner);

	//Pathfinder
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{
	public:
		float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const;
	};
	void createPathMap(Area &Area, AliveObject &owner);
	void calculatePath(Point2D &location, AliveObject &owner);
	Point2D targetLocation;
	void setTargetLocation(Point2D &location);
	

	//Combat
	static const int RANGED_SHOOT_DISTANCE_MAX = 5;
	std::shared_ptr<DynamicObject> combatTarget = nullptr;
	void startCombat(DynamicObject &target);
	void setCombatTarget(DynamicObject &target);
	bool moveOnPath(AliveObject &owner);
	bool targetInFov();

	//True while moving to door and closing it
	//False if no door to close
	bool closeDoor(AliveObject &owner);
	bool wander(AliveObject &owner);
	bool combat(AliveObject &owner);

	virtual void update(AliveObject &owner);

	CreatureAi(){};
};

*/
