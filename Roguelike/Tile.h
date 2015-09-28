#pragma once
#include "GameObject.h"
#include "RarityMod.h"

class VisualEffect;
class DynamicObject;
class Tile : public GameObject
{
public:
	std::shared_ptr<VisualEffect> visualEffectOnCollision;

	bool transparent;
	double walkCost; // walkcost <= 0 == unwalkable else lower better

	bool isPassable(DynamicObject &dynamicObjectMoving);

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	Tile(GameObject gameObject, bool transparent, double walkCost, std::shared_ptr<VisualEffect> visualEffectOnCollision = nullptr) :
		GameObject(gameObject),
		transparent(transparent),
		walkCost(walkCost),
		visualEffectOnCollision(visualEffectOnCollision){};
};

