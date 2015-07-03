#pragma once
#include "GameObject.h"
#include "Item.h"
#include <memory>
#include <vector>

class DynamicObject : public GameObject
{
public:
	bool isDead = false;
	Point2D location;
	bool transparent;
	int healthMax;
	int health;

	void setHealth(int health);
	bool move(Point2D &location);
	void kill();
	virtual bool passable(DynamicObject &dynamicObject);
	virtual void onTakeDamage(DynamicObject &attacker, int amount);
	virtual void onTakeDamageEffect();
	virtual void onDeath();
	virtual void messageDeath();
	virtual void update(){};

	DynamicObject(std::string name, Type type, Glyph glyph, int health, bool transparent = true) :
		GameObject(name, type, glyph),
		transparent(transparent){
		setHealth(health);
	};
};