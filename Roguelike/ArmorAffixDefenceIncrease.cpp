#include "ArmorAffixDefenceIncrease.h"
#include "Engine.h"

std::string ArmorAffixDefenceIncrease::getDescription(){
	return "Defence +" + engine::string.percentage(percentage);
}