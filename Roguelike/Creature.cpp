#include "Creature.h"

std::shared_ptr<Creature> Creature::newCreature(const Creature &creatureTemplate, bool equip){
	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(creatureTemplate));
	if (equip){
		creature->equip(creature->loot.weapons.at(0).get());
	}
	return creature;
}