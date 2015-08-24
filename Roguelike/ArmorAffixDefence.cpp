#include "ArmorAffixDefence.h"
#include "Engine.h"

std::string ArmorAffixDefence::getDescription(){
	return "Defence " + engine::string.percentage(percentage);
}