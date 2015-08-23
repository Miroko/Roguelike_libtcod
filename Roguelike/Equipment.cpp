#include "Equipment.h"
#include "Engine.h"

void Equipment::durabilityHit(double amount){
	durabilityCurrent -= amount;
	if (durabilityCurrent < 0) durabilityCurrent = 0;
}

bool Equipment::isBroken(){
	return durabilityCurrent == 0;
}

std::string Equipment::getStatistics(){
	return engine::string.durability(durabilityCurrent, durabilityMax) + " " + Item::getStatistics();
}