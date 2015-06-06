#pragma once
#include "AliveObject.h"
#include "RarityType.h"
using namespace Rarity;
class Creature : public AliveObject
{
public:
	const RarityType &rarity;	

	Creature(char character, std::string name, Size size, int health, const TCODColor &color, const RarityType &rarity, const Loot &loot) :
		rarity(rarity), AliveObject(Glyph(color * rarity.color, character), name, size, health, loot){};
};