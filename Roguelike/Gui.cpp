#include "Gui.h"

bool Gui::handleKey(TCOD_key_t key){
	if (pickFrame.open) return pickFrame.handleKey(key);
	else if (help.open) help.handleKey(key);
	else if (equipment.open) equipment.handleKey(key);
	else if (inventory.open) return inventory.handleKey(key);
	else if (quest.open) quest.handleKey(key);
	else if (log.open) log.handleKey(key);
	return false;
}

void Gui::render(float elapsed){
	if (log.open) log.render(elapsed);
	if (inventory.open)	inventory.render(elapsed);
	if (equipment.open) equipment.render(elapsed);
	if (pickFrame.open) pickFrame.render(elapsed);
	if (quest.open) quest.render(elapsed);
	if (help.open) help.render(elapsed);
}
