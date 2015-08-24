#include "ItemAffixWeight.h"
#include "Engine.h"

std::string ItemAffixWeight::getDescription(){
	return "Weight " + engine::string.percentage(percentage);
}
