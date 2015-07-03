#include "Item.h"
#include "RarityType.h"
#include "Engine.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}

std::string Item::getDescription(){
	return "";
}

std::string Item::getStatistics(){
	return "";
}

int Item::getValue(){
	int value = 0;
	value += (int)(VALUE_WEIGHT_MULTIPLIER * weight);
	return value;
}

bool Item::isWeapon(){
	return(
		type == WEAPON_MELEE ||
		type == WEAPON_RANGED);
}

bool Item::isArmor(){
	return(
		type == ARMOR_BODY ||
		type == ARMOR_HAND ||
		type == ARMOR_HEAD ||
		type == ARMOR_LEG);
}

void Item::print(int x, int y, int width, int height, TCODConsole &console){
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::amber, console.getDefaultBackground());
	std::string coloredName = "%c" + name + "%c ";
	console.printRectEx(x, y, width, height, TCOD_BKGND_NONE, TCOD_LEFT, coloredName.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	std::string statistics = getStatistics() + std::to_string(getValue()) + "c " + engine::string.weight(weight);
	console.printRectEx(width/2, y, width, height, TCOD_BKGND_NONE, TCOD_LEFT, statistics.c_str());
}

void Item::printWithBg(int x, int y, int width, int height, TCODConsole &console){
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::amber, console.getDefaultBackground());
	std::string coloredName = "%c" + name + "%c ";
	console.printRectEx(x, y, width, height, TCOD_BKGND_SET, TCOD_LEFT, coloredName.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	std::string statistics = getStatistics() + std::to_string(getValue()) + "c " + engine::string.weight(weight);
	console.printRectEx(width / 2, y, width, height, TCOD_BKGND_SET, TCOD_LEFT, statistics.c_str());
}
