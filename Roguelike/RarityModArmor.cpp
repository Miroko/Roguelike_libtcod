#include "RarityModArmor.h"

void RarityModArmor::apply(Armor &armor){
	for (auto &effect : effects){
		effect->apply(armor);
	}
}
