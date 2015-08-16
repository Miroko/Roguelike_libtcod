#pragma once
#include "GameObject.h"
#include "RarityMod.h"

class Tile : public GameObject
{
public:
	bool transparent;
	double walkCost; // walkcost <= 0 == unwalkable else lower better

	Tile(GameObject gameObject, bool transparent, double walkCost) :
		GameObject(gameObject),
		transparent(transparent),
		walkCost(walkCost){};
};

