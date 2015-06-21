#pragma once
#include "OperatableObject.h"
class Door : public OperatableObject
{
public:
	void on();
	void off();
	bool passable();
	
	Door(Glyph openGlyph, Glyph closedGlyph, std::string name, const LootContainer &loot) :
		OperatableObject(openGlyph, closedGlyph, name, 100, loot){};
};

const LootContainer DOOR_LOOT = LootContainer(std::vector<std::shared_ptr<Loot>>({ }));
const std::shared_ptr<Door> WOOD_DOOR = std::shared_ptr<Door>(
	new Door(Glyph(TCODColor::darkSepia, TCODColor::darkestSepia, 'D'),
	Glyph(TCODColor::sepia, TCODColor::darkerSepia, 'D'), "Wooden door", DOOR_LOOT));

