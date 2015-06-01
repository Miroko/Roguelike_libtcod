#pragma once
#include "DynamicObject.h"
#include "memory"

class AliveObject : public DynamicObject
{
	
public:
	//FOV
	std::shared_ptr<TCODMap> fovMap;
	void createFovMap();
	void calculateFov();
	bool inFov(int x, int y);
	//----

	//Pathfinder
	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{
	public:
		float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const;
	};
	void createPathMap();
	void calculatePath(int toX, int toY);
	void moveOnPath();
	//----

	void DynamicObject::update();

	AliveObject(Glyph glyph, std::string name, Size size) :
		DynamicObject(glyph, name, size){};
};

class Human : public AliveObject
{
public:
	Human(std::string name) : AliveObject(Glyph(TCODColor::lighterAmber, '@'), name, MEDIUM){};
	Human();
};

