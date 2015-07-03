#include "Consumable.h"

int Consumable::getValue(){
	return getPotency();
}

int Consumable::getPotency(){
	int potency = 0;
	for (auto &effect : effects){
		//potency += effect->getPotency();
	}
	return potency;
}

std::string Consumable::getStatistics(){
	return std::to_string(getPotency()) + "p ";
}