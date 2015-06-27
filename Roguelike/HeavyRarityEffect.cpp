#include "HeavyRarityEffect.h"
#include "RarityType.h"

void HeavyRarityEffect::apply(Creature &creature){
	RarityEffect::apply(creature);
	float newHealth = creature.healthMax * Random::generator.getFloat(
		MULTIPLIER_MIN * rarityAttachedTo->effectMultiplier,
		MULTIPLIER_MAX * rarityAttachedTo->effectMultiplier
		);
	creature.setHealth(newHealth);
}

void HeavyRarityEffect::apply(Weapon &weapon){
	RarityEffect::apply(weapon);
	float oldWeight = weapon.weight;
	weapon.weight *= Random::generator.getFloat(
		MULTIPLIER_MIN * rarityAttachedTo->effectMultiplier,
		MULTIPLIER_MAX * rarityAttachedTo->effectMultiplier
		);
	weapon.damage *= weapon.weight / oldWeight;
}

void HeavyRarityEffect::apply(Armor &armor){
	RarityEffect::apply(armor);
	float oldWeight = armor.weight;
	armor.weight *= Random::generator.getFloat(
		MULTIPLIER_MIN * rarityAttachedTo->effectMultiplier,
		MULTIPLIER_MAX * rarityAttachedTo->effectMultiplier
		);
	 armor.defence *= armor.weight / oldWeight;
}

void HeavyRarityEffect::applyContinuous(Creature &creature){

}

void HeavyRarityEffect::applyContinuous(Weapon &weapon){

}

void HeavyRarityEffect::applyContinuous(Armor &armor){

}