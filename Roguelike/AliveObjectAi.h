#pragma once
#include "libtcod.hpp"
#include "Door.h"
#include "Rectangle.h"
#include <memory>
#include <deque>
#include <functional>


class Area;
class AliveObject;
class AliveObjectAi
{
private:
	static const int DISTANCE_SMALL = 3;
	static const int DISTANCE_MEDIUM = 6;

	static Rectangle SCAN_AREA;
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
	int energy = 0;
	//FOV
	static const int FOV_RADIUS_MAX = 0;
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap(Area &area);
	void calculateFov(Area &area, AliveObject &owner);
	bool inFov(int x, int y);
	std::vector<std::shared_ptr<Door>> getDoorsInFov(int maxDistance, AliveObject &owner);

	//Pathfinder
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{
	public:
		float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const;
	};
	void createPathMap(Area &area, AliveObject &owner);
	void calculatePath(Point2D &location, AliveObject &owner);
	Point2D targetLocation;
	void setTargetLocation(Point2D &location);

	//Combat
	static const int RANGED_SHOOT_DISTANCE_MAX = 4;
	DynamicObject *combatTarget = nullptr;
	void startCombat(DynamicObject &target);
	void setCombatTarget(DynamicObject &target);
	bool moveOnPath(AliveObject &owner);
	bool targetInFov();

	//True while moving to door and closing it
	//False if no door to close
	bool closeDoor(AliveObject &owner);
	bool wander(AliveObject &owner);
	bool combat(AliveObject &owner);

	void update(AliveObject &owner);

	AliveObjectAi(){};
};

