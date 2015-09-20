#include "Consumable.h"
#include "Creature.h"
#include "RarityAffixConsumable.h"
#include "Engine.h"
#include <algorithm>

std::string Consumable::getStatistics(){
	return 
		engine::string.potency(potency) +
		" " + engine::string.concentration(concentration) +
		" " + Item::getStatistics();
}

void Consumable::onConsume(Creature &consumer){
	for (auto &affix : rarityAffixes){
		RarityAffixConsumable* consumableAffix = static_cast<RarityAffixConsumable*>(affix);
		auto& newEffect = consumableAffix->effect->clone();
		newEffect->modifier = newEffect->modifier * potency;
		newEffect->duration = std::max((int)(newEffect->duration * concentration), 1);
		consumer.addEffect(newEffect);
	}
}

int Consumable::getValue(){
	int value = Item::getValue();
	for (auto &affix : rarityAffixes){
		RarityAffixConsumable* consumableAffix = static_cast<RarityAffixConsumable*>(affix);
		value += consumableAffix->effect->getValue() * potency * concentration;
	}
	return value;
}
