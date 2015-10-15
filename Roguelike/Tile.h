#pragma once
#include "GameObject.h"
#include "RarityMod.h"

class VisualEffect;
class DynamicObject;
class Tile : public GameObject
{
private:
	int movementCost;

public:
	std::shared_ptr<VisualEffect> visualEffectOnCollision;

	int getMovementCost(){ return movementCost; }

	bool isPassable(DynamicObject &dynamicObjectMoving);
	bool isOpen();

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	Tile(GameObject gameObject, int movementCost = 10, std::shared_ptr<VisualEffect> visualEffectOnCollision = nullptr) :
		GameObject(gameObject),
		movementCost(movementCost),
		visualEffectOnCollision(visualEffectOnCollision){};
};

