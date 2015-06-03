#pragma once
#include "GameObject.h"
#include "Loot.h"
class DynamicObject : public GameObject
{

private:

public:
	// Location
	Point2D location;

	//Size
	enum Size
	{
		SMALL,
		MEDIUM,
		LARGE
	};
	Size size;
	virtual bool isBlockedBy(DynamicObject &object);

	//Stats
	int health = 100;
	virtual void takeDamage(int amount);

	//Loot
	Loot *loot;

	virtual void update(){};

	DynamicObject(Glyph glyph, std::string name, Size size, Loot *loot) : GameObject(glyph, name), size(size), loot(loot){};
};