#include "RarityModWeapon.h"


void RarityModWeapon::apply(Weapon &weapon){
	for (auto &effect : effects){
		effect->apply(weapon);
	}
}

