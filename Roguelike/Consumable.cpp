#include "Consumable.h"
#include "Creature.h"
#include "RarityAffixConsumable.h"

void Consumable::onConsume(Creature &consumer){
	for (auto &affix : rarityAffixes){
		RarityAffixConsumable* consumableAffix = static_cast<RarityAffixConsumable*>(affix);
		consumer.addEffect(consumableAffix->effect->clone());
	}
}

int Consumable::getValue(){
	int value = Item::getValue();
	for (auto &affix : rarityAffixes){
		RarityAffixConsumable* consumableAffix = static_cast<RarityAffixConsumable*>(affix);
		value += consumableAffix->effect->getValue();
	}
	return value;
}
