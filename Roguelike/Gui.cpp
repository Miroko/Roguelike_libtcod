#include "Gui.h"

bool Gui::handleKey(TCOD_key_t key){	
	bool handled = false;
	if (inventory.handleKey(key)) handled = true;
	if (equipment.handleKey(key)) handled = true;
	if (quest.handleKey(key)) handled = true;
	if (help.handleKey(key)) handled = true;
	if (log.handleKey(key)) handled = true;
	if (pickFrame.handleKey(key)) handled = true;
	if (inspection.handleKey(key)) handled = true;
	if (statistics.handleKey(key)) handled = true;
	if (trade.handleKey(key)) handled = true;
	if (dialog.handleKey(key)) handled = true;
	return handled;
}

void Gui::render(float elapsed){
	if (inspection.isOpen) inspection.render(elapsed);
	if (log.isOpen) log.render(elapsed);
	if (statistics.isOpen) statistics.render(elapsed);
	if (inventory.isOpen) inventory.render(elapsed);
	if (equipment.isOpen) equipment.render(elapsed);
	if (pickFrame.isOpen) pickFrame.render(elapsed);
	if (quest.isOpen) quest.render(elapsed);
	if (help.isOpen) help.render(elapsed);
	if (dialog.isOpen) dialog.render(elapsed);
	if (trade.isOpen) trade.render(elapsed);
}
