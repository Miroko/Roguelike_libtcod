#pragma once
#include "GameObject.h"
#include "Item.h"
#include "LootContainer.h"
#include <memory>
#include <vector>
class DynamicObject : public GameObject
{

public:
	bool isDead = false;

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

	//Stats
	int healthMax;
	int health;

	virtual void onTakeDamage(int amount);
	virtual void onDeath();

	virtual void messageDeath();

	const LootContainer &loot;

	virtual void update(){};

	DynamicObject(Glyph glyph, std::string name, Size size, bool transparent, int health, const LootContainer &loot) :
		GameObject(glyph, name, transparent), size(size), health(health), healthMax(health), loot(loot){};
};