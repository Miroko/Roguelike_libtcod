#include "Creature.h"
#include "RarityEffect.h"

void Creature::equip(EquipmentContainer &equipment){
	equipment.equipOn(*this);
}

void Creature::update(){
	//Rarity effects
	rarityEffect->applyContinuous(*this);
	if (weapon != nullptr) rarityEffect->applyContinuous(*weapon);
	if (armorHead != nullptr) rarityEffect->applyContinuous(*armorHead);
	if (armorBody != nullptr) rarityEffect->applyContinuous(*armorBody);
	if (armorHand != nullptr) rarityEffect->applyContinuous(*armorHand);
	if (armorLeg != nullptr) rarityEffect->applyContinuous(*armorLeg);

	AliveObject::update();
}