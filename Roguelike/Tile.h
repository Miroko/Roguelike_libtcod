#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	bool transparent;
	float walkCost;
	float staminaCostMultiplierForMove;

	Tile(std::string name, Type type, Glyph glyph, bool transparent = true, float walkCost = 10.0f, float staminaCostMultiplierForMove = 1.0f) :
		GameObject(name, type, glyph),
		transparent(transparent),
		walkCost(walkCost),
		staminaCostMultiplierForMove(staminaCostMultiplierForMove){};
};

