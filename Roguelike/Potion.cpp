#include "Potion.h"
#include "Creature.h"
#include "Engine.h"

void Potion::onConsume(Creature &consumer){
	for (auto &effect : effects){
		consumer.addEffect(effect);
	}
}

int Potion::getValue(){
	return value;
}

std::string Potion::getStatistics(){
	return Item::getStatistics();
}
