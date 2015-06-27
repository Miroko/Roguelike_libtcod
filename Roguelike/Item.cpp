#include "Item.h"
#include "RarityType.h"
#include "String.h"

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
	value += VALUE_WEIGHT_MULTIPLIER * weight;
	return value;
}

void Item::print(int x, int y, int width, int height, TCODConsole &console){
	TCODConsole::setColorControl(TCOD_COLCTRL_1, rarity->color, console.getDefaultBackground());
	std::string coloredName = "%c" + name + "%c ";
	console.printRectEx(x, y, width, height, TCOD_BKGND_NONE, TCOD_LEFT, coloredName.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	std::string statistics = getStatistics() + std::to_string(getValue()) + "c " + String::weight(weight);
	console.printRectEx(width/2, y, width, height, TCOD_BKGND_NONE, TCOD_LEFT, statistics.c_str());
}

void Item::printWithBg(int x, int y, int width, int height, TCODConsole &console){
	TCODConsole::setColorControl(TCOD_COLCTRL_1, rarity->color, console.getDefaultBackground());
	std::string coloredName = "%c" + name + "%c ";
	console.printRectEx(x, y, width, height, TCOD_BKGND_SET, TCOD_LEFT, coloredName.c_str(), TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

	std::string statistics = getStatistics() + std::to_string(getValue()) + "c " + String::weight(weight);
	console.printRectEx(width / 2, y, width, height, TCOD_BKGND_SET, TCOD_LEFT, statistics.c_str());
}
