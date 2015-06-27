#include "RarityEffect.h"
#include "RarityType.h"

void RarityEffect::apply(Creature &creature){
	creature.rarityEffect = this;
}

void RarityEffect::apply(Weapon &weapon){
	weapon.rarityEffect = this;
}

void RarityEffect::apply(Armor &armor){
	armor.rarityEffect = this;
}

void RarityEffect::applyContinuous(Creature &creature){

}

void RarityEffect::applyContinuous(Weapon &weapon){

}

void RarityEffect::applyContinuous(Armor &armor){

}
