#pragma once
#include "OperatableObject.h"

class Container : public OperatableObject
{
private:
	bool opened;
	double lootDropsFromMax;
	bool isLarge;

	Glyph openGlyph;
	Glyph closedGlyph;

public:
	void dropLoot(Creature &looter);

	void operate(Creature &user) override;
	bool isPassable(DynamicObject &dynamicObject) override;
	void onDeath() override;

	std::shared_ptr<OperatableObject> copy();

	Container(
		std::string name, Glyph open, Glyph closed, int health,
		double lootDropsFromMax, bool isLarge = false)
		:
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::CHEST,
		closed),
		health)),
		openGlyph(open),
		closedGlyph(closed),
		opened(false),
		lootDropsFromMax(lootDropsFromMax),
		isLarge(isLarge){};
};

