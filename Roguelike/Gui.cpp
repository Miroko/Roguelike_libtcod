#include "Gui.h"

bool Gui::handleKey(TCOD_key_t key){
	if (pickFrame.isOpen) return pickFrame.handleKey(key);
	else if (help.isOpen) return help.handleKey(key);
	else if (equipment.isOpen) return equipment.handleKey(key);
	else if (inventory.isOpen) return inventory.handleKey(key);
	else if (quest.isOpen) return quest.handleKey(key);
	else if (log.isOpen) log.handleKey(key);
	return false;
}

void Gui::render(float elapsed){
	if (log.isOpen) log.render(elapsed);
	if (inventory.isOpen) inventory.render(elapsed);
	if (equipment.isOpen) equipment.render(elapsed);
	if (pickFrame.isOpen) pickFrame.render(elapsed);
	if (quest.isOpen) quest.render(elapsed);
	if (help.isOpen) help.render(elapsed);
}
