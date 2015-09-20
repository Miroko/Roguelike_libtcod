#include "ItemAffixWeight.h"
#include "Item.h"
#include "Engine.h"

std::string ItemAffixWeight::getDescription(GameObject &ownerObject){
	Item &ownerItem = static_cast<Item&>(ownerObject);
	return "Weight " + engine::string.weightKg(ownerItem.getWeightBase() * getWeightModifier(), true, 2, true);
}
