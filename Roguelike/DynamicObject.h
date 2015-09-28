#pragma once
#include "GameObject.h"
#include "Item.h"
#include <memory>
#include <vector>

class VisualEffect;
class DynamicObject : public GameObject
{
private:
	std::shared_ptr<VisualEffect> visualEffectOnTakeDamage;

	int healthCurrent;
	int healthMax;

public:
	Point2D location;
	bool transparent;

	void destroy();

	virtual int getHealthCurrent();
	virtual int getHealthMax();
	virtual void healthHit(int amount);
	virtual bool move(Point2D &location);
	virtual void onMove();
	virtual bool isPassable(DynamicObject &dynamicObject);
	virtual void takeDamage(DynamicObject &attacker, double amount);
	virtual void onDeath();
	virtual void messageDeath();
	virtual void update(){};

	DynamicObject(GameObject gameObject, int health, bool transparent = true, std::shared_ptr<VisualEffect> visualEffectOnTakeDamage = nullptr) :
		GameObject(gameObject),
		transparent(transparent),
		healthCurrent(health),
		healthMax(health),
		visualEffectOnTakeDamage(visualEffectOnTakeDamage){
	};
};