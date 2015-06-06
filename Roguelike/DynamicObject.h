#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Loot.h"
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
	virtual bool isBlockedBy(DynamicObject &object);

	//Stats
	int health;

	virtual void onTakeDamage(int amount);
	virtual void onDeath();

	const Loot &loot;

	virtual std::vector<std::shared_ptr<Item>> generateLoot();

	virtual void update(){};

	DynamicObject(Glyph glyph, std::string name, Size size, int health, const Loot &loot) :
		GameObject(glyph, name), size(size), health(health), loot(loot){};
};