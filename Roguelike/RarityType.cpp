#include "RarityType.h"
#include "Engine.h"
#include <vector>
#include <memory>

std::vector<RarityModCreature*> RarityType::getRandomCreatureMods(){
	std::vector<RarityModCreature*> rarityMods;
	for (int modNumber = engine::random.generator->getInt(0, modsPerItemMax); modNumber > 0; --modNumber){
		float roll = engine::random.generator->getFloat(0.0, 1.0);
		if (roll < modRollChance){
			int randomIndex = engine::random.generator->getInt(0, creatureMods.size() - 1);
			rarityMods.push_back(&creatureMods.at(randomIndex));
		}
	}
	return rarityMods;
}

std::vector<RarityModWeapon*> RarityType::getRandomWeaponMods(){
	std::vector<RarityModWeapon*> rarityMods;
	for (int modNumber = engine::random.generator->getInt(0, modsPerItemMax); modNumber > 0; --modNumber){
		float roll = engine::random.generator->getFloat(0.0, 1.0);
		if (roll < modRollChance){
			int randomIndex = engine::random.generator->getInt(0, weaponMods.size() - 1);
			rarityMods.push_back(&weaponMods.at(randomIndex));
		}
	}
	return rarityMods;
}

std::vector<RarityModArmor*> RarityType::getRandomArmorMods(){
	std::vector<RarityModArmor*> rarityMods;
	for (int modNumber = engine::random.generator->getInt(0, modsPerItemMax); modNumber > 0; --modNumber){
		float roll = engine::random.generator->getFloat(0.0, 1.0);
		if (roll < modRollChance){
			int randomIndex = engine::random.generator->getInt(0, armorMods.size() - 1);
			rarityMods.push_back(&armorMods.at(randomIndex));
		}
	}
	return rarityMods;
}