#pragma once
#include "Item.h"
#include "AliveObject.h"
#include "Heal.h"

class Consumable : public Item
{
public:

	std::vector<std::shared_ptr<AliveObjectEffect>> effects;

	std::string getDescription();
	int getValue();

	Consumable(std::string name, std::vector<std::shared_ptr<AliveObjectEffect>> effects, Glyph glyph, float weight)
		: Item(glyph, name, weight, CONSUMABLE), effects(effects){};
};

const std::vector<std::shared_ptr<AliveObjectEffect>> HEALTH_POTION_EFFECTS = std::vector<std::shared_ptr<AliveObjectEffect>> ({ HEAL });
const std::shared_ptr<Consumable> HEALTH_POTION = std::shared_ptr<Consumable>(new Consumable("Health potion", HEALTH_POTION_EFFECTS, Glyph(TCODColor::lightRed, 'p'), 0.2));
