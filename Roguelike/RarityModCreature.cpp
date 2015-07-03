#include "RarityModCreature.h"

void RarityModCreature::apply(Creature &creature){
	for (auto &effect : effects){
		effect->apply(creature);
	}
}