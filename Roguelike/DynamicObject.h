#pragma once
#include "GameObject.h"
#include "Item.h"
#include <memory>
#include <vector>

class DynamicObject : public GameObject
{
private:
	int healthCurrent;
	int healthMax;

public:
	bool isDead;
	Point2D location;
	bool transparent;

	virtual int getHealthCurrent();
	virtual int getHealthMax();
	virtual void healthHit(int amount);

	void kill();

	virtual bool move(Point2D &location);
	virtual void onMove();
	virtual bool passable(DynamicObject &dynamicObject);
	virtual void onTakeDamage(DynamicObject &attacker, double amount);
	virtual void onTakeDamageEffect();
	virtual void onDeath();
	virtual void messageDeath();
	virtual void update(){};

	DynamicObject(GameObject gameObject, int health, bool transparent = true) :
		GameObject(gameObject),
		transparent(transparent),
		healthCurrent(health),
		healthMax(health){
		isDead = false;
	};
};