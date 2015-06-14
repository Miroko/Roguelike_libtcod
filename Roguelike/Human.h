#pragma once
#include "Race.h"
#include "Loot.h"
#include "Creature.h"
#include <memory>
#include <vector>

class Human : public Race{
	public:		
		Human() : Race("Men"){};
	};

const Loot MAN_LOOT = Loot(std::vector<std::shared_ptr<Weapon>>({ SWORD }));
const Creature MAN = Creature('h', "Man", DynamicObject::MEDIUM, 30, TCODColor::lightAmber, COMMON, MAN_LOOT);
