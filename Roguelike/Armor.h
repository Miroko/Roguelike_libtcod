#pragma once
#include "Equipment.h"
class Armor : public Equipment
{
public:
	int defence;

	std::string getDescription();
	int getValue();

	Armor(std::string name, Glyph glyph, float weight, int defence, Type type) : Equipment(glyph, name, weight, type), defence(defence){};
};

const std::shared_ptr<Armor> LEATHER_HEAD = std::shared_ptr<Armor>(new Armor("Leather cap", Glyph(TCODColor::brass, 'c'), 0.5, 1, Item::ARMOR_HEAD));
const std::shared_ptr<Armor> LEATHER_BODY = std::shared_ptr<Armor>(new Armor("Leather body", Glyph(TCODColor::brass, 'B'), 5.0, 3, Item::ARMOR_BODY));
const std::shared_ptr<Armor> LEATHER_HAND = std::shared_ptr<Armor>(new Armor("Leather gloves", Glyph(TCODColor::brass, 'g'), 0.5, 1, Item::ARMOR_HAND));
const std::shared_ptr<Armor> LEATHER_LEG = std::shared_ptr<Armor>(new Armor("Leather boots", Glyph(TCODColor::brass, 'b'), 2.0, 2, Item::ARMOR_LEG));
