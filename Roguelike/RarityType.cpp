#include "RarityType.h"
#include "RarityEffect.h"
#include "Random.h"

RarityEffect* RarityType::getRandomEffect(){
	if (!effects.empty()){
		int randomIndex = Random::generator.getInt(0, effects.size() - 1);
		RarityEffect& effect = *effects.at(randomIndex);
		effect.rarityAttachedTo = this;
		return &effect;
	}
	else return nullptr;
}

void RarityType::apply(Creature &creature){
	creature.rarity = this;
	creature.glyph.fgColor = creature.glyph.fgColor * color;
	getRandomEffect()->apply(creature);
}

void RarityType::apply(Weapon &weapon){
	weapon.rarity = this;
	weapon.glyph.fgColor = weapon.glyph.fgColor * color;
	getRandomEffect()->apply(weapon);
}

void RarityType::apply(Armor &armor){
	armor.rarity = this;
	armor.glyph.fgColor = armor.glyph.fgColor * color;
	getRandomEffect()->apply(armor);
}

void RarityType::apply(Consumable &consumable){
	consumable.rarity = this;
}
