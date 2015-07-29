#include "RarityModCreature.h"

void RarityModCreature::apply(Creature &creature){
	effect->apply(creature);
}