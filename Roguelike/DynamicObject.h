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
	int healthCurrent;

	void setHealth(int healthCurrent);
	virtual bool move(Point2D &location);
	virtual void onMove();
	void kill();
	virtual bool passable(DynamicObject &dynamicObject);
	virtual void onTakeDamage(DynamicObject &attacker, int amount);
	virtual void onTakeDamageEffect();
	virtual void onDeath();
	virtual void messageDeath();
	virtual void update(){};

	DynamicObject(GameObject gameObject, int healthCurrent, bool transparent = true) :
		GameObject(gameObject),
		transparent(transparent){
		setHealth(healthCurrent);
	};
};