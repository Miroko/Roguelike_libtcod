#include "Creature.h"

std::shared_ptr<Creature> Creature::newCreature(const Creature &creatureTemplate){
	return std::shared_ptr<Creature>(new Creature(creatureTemplate));
}