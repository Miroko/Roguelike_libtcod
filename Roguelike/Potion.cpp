#include "Potion.h"
#include "Creature.h"

void Potion::onConsume(Creature &consumer){
	for (auto &effect : effects){
		consumer.addEffect(effect);
	}
}

int Potion::getValue(){
	return Item::getValue() + potency;
}

std::string Potion::getStatistics(){
	return std::to_string(potency) + "p " + Item::getStatistics();
}
