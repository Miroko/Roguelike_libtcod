#pragma once
#include "Equipment.h"
#include "Random.h"
#include <memory>

class Weapon : public Equipment
{
public:
	int damage;

	std::string getStatistics();
	int getValue();

	Weapon(std::string name, Glyph glyph, float weight, int damage, Type type) : Equipment(name, glyph, weight, type), damage(damage){};
};

