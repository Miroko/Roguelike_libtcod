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

	//Stats
	int healthMax;
	int health;

	virtual void onTakeDamage(int amount);
	virtual void onDeath();

	const Loot &loot;

	virtual std::vector<std::shared_ptr<Item>> generateLoot();

	virtual void update(){};

	DynamicObject(Glyph glyph, std::string name, Size size, bool transparent, int health, const Loot &loot) :
		GameObject(glyph, name, transparent), size(size), health(health), healthMax(health), loot(loot){};
};