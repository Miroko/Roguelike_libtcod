#pragma once
#include "GameObject.h"
#include "RarityMod.h"

class VisualEffect;
class DynamicObject;
class Tile : public GameObject
{
private:
	double walkCost; // walkcost <= 0 == unwalkable else lower better

public:
	std::shared_ptr<VisualEffect> visualEffectOnCollision;

	double getWalkCost(){ return walkCost; }

	bool isPassable(DynamicObject &dynamicObjectMoving);
	bool isOpen();

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	Tile(GameObject gameObject, double walkCost, std::shared_ptr<VisualEffect> visualEffectOnCollision = nullptr) :
		GameObject(gameObject),
		walkCost(walkCost),
		visualEffectOnCollision(visualEffectOnCollision){};
};

