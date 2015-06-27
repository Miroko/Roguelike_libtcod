#pragma once
#include "GameObject.h"
#include "Item.h"
#include "LootContainer.h"
#include <memory>
#include <vector>

class DynamicObject : public GameObject
{
public:
	LootContainer *loot = nullptr;

	bool isDead = false;

	Point2D location;

	bool transparent;

	//Stats
	int healthMax;
	int health;
	void setHealth(int health);

	virtual bool passable(DynamicObject &dynamicObject);

	virtual void onTakeDamage(DynamicObject &attacker, int amount);
	virtual void onTakeDamageEffect();
	virtual void onDeath();

	virtual void messageDeath();

	virtual void update(){};

	DynamicObject(std::string name, Glyph glyph, int health, bool transparent = true) :
		GameObject(name, glyph),
		transparent(transparent){
		setHealth(health);
	};
};